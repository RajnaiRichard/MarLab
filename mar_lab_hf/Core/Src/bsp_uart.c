/** TODO 1. UART feladat
 * Az UART kommunikációs feladat megoldása.
 * Az itt található függvények elsődleges feladata a log.c logolási funkcióinak kiszolgálása, valamint
 * a  mainloop.c számára lehetővé tenni, hogy soros porton egyetlen bájtos parancsokat
 * fogadjon.
 *
 * Az inicializálás kereteiben belül egyrészt konfigurálni kell a mikrovezérlő megfelelő lábait
 * (alternate function, push-pull stb.), valamint az UART perifériát (baud rate, stop bitek száma stb.)
 * Ehhez a MARCOM.ioc fájlban található grafikus konfigurátort használjuk, és az általa generált inicializáló
 * függvényt hívjuk meg itt az UART_Init() függvényben.
 *
 * Ezután a UART_SendString() függvényben már meg lehet írni egy string küldését. Ezúttal
 * nem blokkoló, interrupt alapú küldést használunk, hogy küldés közben a rendszer többi
 * funkciója ne akadjon meg.
 *
 * A feladat sikeres elkészítése után oszcilloszkóppal vizsgáljon meg egy UART keretet (PD8 pin), és a jegyzőkönyvben
 * helyezzen el egy screenshotot, melyen látszik a keret eleje, vége, és mutassa be az egyes bitek pontos jelentését
 * (vagyis hogy mit küldött éppen). Ellenőrizze a scope kurzorai segítségével a baud rate-et.
 * Nagyon figyeljen oda, hogy a tüskesor lábait nehogy rövidre zárja! A rövidzárból eredő károkért a hallgató felel!
 * Földpontnak használja péládul az RS-232 csatlakozó csavarját.
 *
 * TODO 2. UART adatfogadás kezelése
 * Ez a feladat az UART adatfogadásról szól, mivel az előző feladat csak a küldést tartalmazza.
 * A HAL koncepciója szerint az interruptokról callback függvényeken keresztül kapunk
 * értesítést, melyeket a beépített interrupt kezelő hív meg. Ezért néz ki az igazi interrupt kezelő
 * (USART3_IRQHandler() az stm32f4xx_it.c-ben) függvény úgy, ahogy: csak egy már a HAL-lal kapott
 * kezelő függvény meghívását látjuk benne.
 *
 * Fogadott adatokról értesítést a HAL_UART_RxCpltCallback() függvény segítségével kapunk, így a kapott adatok
 * feldolgozását itt kell megoldani. Ezen kívül az interruptos fogadást engedélyezni kell a UART_Init()-ben.
 * Jelen esetben a callback függvényben a fogadott bájtot csak elmentjük a lastReceivedUartCommand globális változóba, 
 * melyet a főciklus figyel a mainloop.c-ben, és szükség esetén reagál rá. A feladat másik része éppen ezért a
 * mainloop.c-ben található.
 */
 
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "string.h"
#include "usart.h"
#include "bat.h"

/* ----------------- Publikus globális változók ----------------- */

/** Last received command. 0 if none. */
uint8_t lastReceivedUartCommand = 0;

/* ----------------- Belső, globális változók ----------------- */

// Egyetlen bájtos adatfogadási buffer
char rxBuffer;
// Ide másoljuk a küldés alatt álló stringet. Az UART_SendString() használja.
#define TXBUFFERSIZE 255
char txBuffer[TXBUFFERSIZE];

/* ----------------- Publikus függvények ----------------- */

/** Inicializálás */
HAL_StatusTypeDef UART_Init()
{
	// TODO 1. UART feladat
	// Állítsuk be az UART perifériát a MARCOM.ioc fájlban az alábbiak szerint:
	//  - Instance: USART3
	//  - Aszinkron mód
	//  - Nincs hardveres flow control
	//  - TX vonal: PD8, RX vonal: PD9
	//  - 115200 bit/s
	//  - 8N1 mód (vagyis 8 adatbit van, nincs paritás és 1 stop bit van)
	//  - a küldést és fogadást is engedélyezni kell
	//  - Oversampling: 16
	//  - Az NVIC beállításoknál engedélyezzük az USART3 global interrupt-ot
	// Generálás után includeoljuk az usart.h fájlt, majd hívjuk meg a benne lévő
	// inicializáló függvényt. A későbbiekben az USART3 perifériát a huart3 
	// handle változón keresztül érhetjük el (ld. usart.h).
	//MX_USART2_UART_Init();

	// TODO 2. UART adatfogadás kezelése
	// Itt kell engedélyezni az adatok fogadását. Ehhez kérje 1 byte fogadását 
	// az rxBuffer-be, nem blokkoló módon a HAL_UART_Receive_IT() meghívásával. 
	// A HAL_UART_Receive_IT() 2. paraméterének típusa (uint8_t*) kell legyen, 
	// így az rxBuffer-t castolni kell.
	HAL_UART_Receive_IT(&huart3, (uint8_t*)&rxBuffer, 1);
	return HAL_OK;
}

/** String küldése, nem blokkolva. */
HAL_StatusTypeDef UART_SendString(char *str)
{
	// TODO 1. UART feladat
	// Várjon addig, amig az UART periféria készen nem áll az adatküldésre.
	// Akkor tudunk küldeni, ha a huart3.gState vagy HAL_UART_STATE_READY, vagy 
	// HAL_UART_STATE_BUSY_RX (vagyis csak fogadás van folyamatban).
	// (Ez a várakozás részben blokkolóvá teszi az amúgy nem blokkoló küldést, de
	// az egyszerűség kedvéért most ezt bevállaljuk, mert különben egy várakozó sort kellene
	// készíteni a küldéseknek, ami meghaladja a mérés célkitűzését.)
	while(!(huart3.gState == HAL_UART_STATE_READY || huart3.gState==HAL_UART_STATE_BUSY_RX))
	{}

	// Ha ide eljutottunk, akkor az UART periféria készen áll az adatküldésre.
	// A paraméterként kapott stringet nem blokkolva küldje el a HAL_UART_Transmit_IT()
	// függvény segítségével. Figyeljen rá, hogy ha visszatér ebből a függvényből, az str által
	// mutatott hely már megváltozhat, pedig még nem küldtük el. Így itt másolja át a tartalmát
	// a txBuffer-be (de csak maximum TXBUFFERSIZE bájtot)! (strncpy()).
	// A HAL_UART_Transmit_IT() 2. paraméterének típusa (uint8_t*) kell legyen, így a txBuffer-t
	// castolni kell.
		int size;
		if(strlen(str)>TXBUFFERSIZE)
			size=TXBUFFERSIZE;
		else
			size=strlen(str);

		strncpy(txBuffer,str,size);
		HAL_UART_Transmit_IT(&huart3, (uint8_t*)txBuffer, size);
	return HAL_OK;
}


/* ----------------- Megszakításkezelő és callback függvények ----------------- */

// TODO 2. UART adatfogadás kezelése
// Érvényesítsük a HAL_UART_RxCpltCallback() függvény definícióját (vegyük ki a kommentjeleket)

/** Callback függvény, mely sikeres adatfogadás végét jelzi. */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *handle)
{
	// TODO 2. UART adatfogadás kezelése
	// Ennek a callback függvénynek a meghívásakor a fogadott adatok az rxBufferben vannak,
	// mivel az Init végén oda kértük a mentésüket.
	// Megjegyzés: a handle->pRxBuffPtr a következő szabad bájtra mutat, nem a buffer elejére!
	// Mentse el azt az egy bájtot a lastReceivedUartCommand globális változóba, majd
	// az HAL_UART_Receive_IT() meghívásával kérje a következő bájt fogadását.
	// Ha ez utóbbi elmarad, akkor a további bejövő adatokról nem szerzünk majd tudomást,
	// mert nem kértük fogadásukat.
	lastReceivedUartCommand=rxBuffer;
	HAL_UART_Receive_IT(handle,(uint8_t*)&rxBuffer,1);
}

