/**
 * Llibreria per controlar les pulsacións de botons conectats als pins del micro controlador PIC18F45K22
 */

typedef unsigned char byte;

/**
 * @brief Configures pin PORT'port'bits.R'port''pin' as an input of a button.
 * @param port: El port del pin, ej: 'A','B','C','D','E'.
 * @param pin: El numero del pin, normalment entre 0 i 7, menys pel port E, que només te del 0 al 2.
 */
void configButton(char port, byte pin, byte raisingEdge);

/**
 * @brief Detector de inputs del puerto A.
 * @param pin el pin del que se quiere detectar la entrada, este tiene que estar entre 0 i 7
 */
int inputDetectorRA(byte pin);


/**
 * @brief Detector de inputs del puerto B.
 * @param pin el pin del que se quiere detectar la entrada, este tiene que estar entre 0 i 7
 */
int inputDetectorRB(byte pin);


/**
 * @brief Detector de inputs del puerto C.
 * @param pin el pin del que se quiere detectar la entrada, este tiene que estar entre 0 i 7
 */
int inputDetectorRC(byte pin);


/**
 * @brief Detector de inputs del puerto D.
 * @param pin el pin del que se quiere detectar la entrada, este tiene que estar entre 0 i 7
 */
int inputDetectorRD(byte pin);



/**
 * @brief Detector de inputs del puerto E.
 * @param pin el pin del que se quiere detectar la entrada, este tiene que estar entre 0 i 3
 */
int inputDetectorRE(byte pin);