/*
SPI (Serial Peripheral Interface) library

Clock polarity and phase:
See https://en.wikipedia.org/wiki/Serial_Peripheral_Interface#Clock_polarity_and_phase

By default, the library is set to use CPOL = 0, CPHA = 0 (most devices use this).
If a particular device needs to use a different SPI mode, it must change the mode,
send its message(s), then change the mode back immediately after. All devices
assume that SPI is using mode 0 when calling send_spi() if they don't change
the mode themselves.

Mode    CPOL    CPHA
0       0       0
1       0       1
2       1       0
3       1       1
*/

#include <spi/spi.h>

// SPI pins on microcontroller
#define CLK     PB7
#define MISO    PB0
#define MOSI    PB1
#define SS      PD3


// Initializes a pin as an output pin for a CS line to control a SPI device.
void init_cs(uint8_t pin, ddr_t ddr) {
    *ddr |= _BV(pin);
}

// Sets an output pin's value to be low.
void set_cs_low(uint8_t pin, port_t port) {
    *port &= ~_BV(pin);
}

// Sets an output pin's value to be high.
void set_cs_high(uint8_t pin, port_t port) {
    *port |= _BV(pin);
}


// Initializes the SPI library (registers and output pins).
// Before SPI is enabled, PPRSPI must be 0
void init_spi(void) {
    // make CLK, MOSI, and SS pins output
    DDRB |= _BV(CLK) | _BV(MOSI);
    DDRD |= _BV(SS);
    // enable SPI, set mode to master, set SCK freq to f_io/64
    // TODO - can we run SPI faster? check each SPI device's datasheet for max frequency
    SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

/*
Sends an 8-bit SPI message and receives 8 bits of data back.
data - 8 bits of data to send
Returns - 8 bits of data received
*/
uint8_t send_spi(uint8_t data) {
    uint16_t timeout = UINT16_MAX;
    // Set the data register with data to transmit
    SPDR = data;
    // Wait until the finished bit goes high (or times out)
    while (!(SPSR & _BV(SPIF)) && timeout--);
    // Return the received data (contents of the data register)
    return SPDR;
}


/*
Sets the CPOL and CPHA values for SPI.
cpol - 0 or 1, otherwise does nothing
cpha - 0 or 1, otherwise does nothing
*/
void set_spi_cpol_cpha(uint8_t cpol, uint8_t cpha) {
    if (cpol == 0) {
        SPCR &= ~_BV(CPOL);
    } else if (cpol == 1) {
        SPCR |= _BV(CPOL);
    }
    // else, don't change CPOL

    if (cpha == 0) {
        SPCR &= ~_BV(CPHA);
    } else if (cpha == 1) {
        SPCR |= _BV(CPHA);
    }
    // else, don't change CPHA
}

/*
Resets the CPOL and CPHA values for SPI (sets CPOL = 0, CPHA = 0).
*/
void reset_spi_cpol_cpha(void) {
    set_spi_cpol_cpha(0, 0);
}

/*
Sets the SPI mode (corresponds to CPOL and CPHA).
mode - 0, 1, 2, or 3 (see table at top of file), otherwise does nothing
*/
void set_spi_mode(uint8_t mode) {
    if (mode == 0) {
        set_spi_cpol_cpha(0, 0);
    } else if (mode == 1) {
        set_spi_cpol_cpha(0, 1);
    } else if (mode == 2) {
        set_spi_cpol_cpha(1, 0);
    } else if (mode == 3) {
        set_spi_cpol_cpha(1, 1);
    }
    // else, don't change the mode
}
