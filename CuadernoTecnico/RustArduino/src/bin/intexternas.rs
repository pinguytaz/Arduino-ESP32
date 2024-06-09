/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Ejemplo de desarrollo en Arduino con el lenguage Rust.                                 *
 *               este ejemplo pretender mostrar el uso interrupciones externas en lugar de estar        *
 *               mirando constantemente el valor del boton y lo que controla es el estado               *
 *               tendremos 7 estados y se representaran en binario con los LEDs                         *
 *               Tambien controlamos el rebote del boton no cambiando estado hasta que el anterior se   *
 *               procese                                                                                *
 *                                                                                                      *
 *  Historico:                                                                                          *
 *      Creación:  0.1.0 Abril 2024  FJRN                                                               *
 *                                                                                                      *
 * Añadir los crates:                                                                                   *
 *     avr_device   añadir en Cargo.toml                                                                * 
 *               [dependencies.avr-device]                                                              *
 *               version = "0.5.4"                                                                      *
 *               features = ["atmega328p"]                                                              *
 *                                                                                                      *
 ********************************************************************************************************/
#![no_std]           // No usa libreria estandard, sino la core al tratarse de embebido
#![no_main]          // No usa la funcion main como inicio

#![feature(abi_avr_interrupt)]  // Aplica la convención de llamada correcta a los controladores de interrupciones.

use panic_halt as _;    // Tratamiento de ecepciones
use core::sync::atomic::{AtomicBool, AtomicI8, Ordering};    // Tratamiento de variables atomicas.

// Variables atomicas estaticas que son con las que nos comunicaremos con la funcion de interrupción
static ESTADO: AtomicI8 = AtomicI8::new(0);     // Atomica de controla el estado de 0 a 7.
static REBOTE: AtomicBool = AtomicBool::new(false);    // Atomica de control de rebote solo cambia estado una vez al uso

#[arduino_hal::entry]      // Punto de entrada del programa
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    // Habilitamos INT0 en flanco de bajada, es decir al pulsar el boton y suelta 
    dp.EXINT.eicra.modify(|_, w| w.isc0().bits(0x02));     // Registro EICRA isc0() Bits 0:1
    //dp.EXINT.eicra.modify(|_, w| w.isc0().bits(0x03));     // Registro EICRA isc0() Bits 0:1
    dp.EXINT.eimsk.modify(|_, w| w.int0().set_bit());     //  Registro EIMSK INT0 bit0 a 1. 

    let mut led1 = pins.d12.into_output();  // Lo pone como salida
    let mut led2 = pins.d11.into_output();
    let mut led3 = pins.d10.into_output();


    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);      // Configuracion de consola

    unsafe { avr_device::interrupt::enable() };        // Habilita las interrupciones

    // Este loop seria la función loop() de un programa arduino normal.
    loop {
        match estado() {
            0 => {
                led1.set_low();
                led2.set_low();
                led3.set_low();
            },
            1 => {
                led1.set_high();
                led2.set_low();
                led3.set_low();
            },
            2 => {
                led1.set_low();
                led2.set_high();
                led3.set_low();
            },
            3 => {
                led1.set_high();
                led2.set_high();
                led3.set_low();
            },
            4 => {
                led1.set_low();
                led2.set_low();
                led3.set_high();
            },
            5 => {
                led1.set_high();
                led2.set_low();
                led3.set_high();
            },
            6 => {
                led1.set_low();
                led2.set_high();
                led3.set_high();
            },
            7 => {
                led1.set_high();
                led2.set_high();
                led3.set_high();
             },
             _ =>  { _ = ufmt::uwriteln!(serial, "Estado desconocido"); }

        }
        REBOTE.store(false, Ordering::SeqCst);   // Se trato por lo tanto podemos permitir nuevos cambios de estado.
        arduino_hal::delay_ms(1000);
    }
}

fn  estado() -> i8 {
    ESTADO.load(Ordering::SeqCst)
}

fn  es_rebote() -> bool {
    REBOTE.load(Ordering::SeqCst)
}

/*************  Definimos la funcion que se llamara al generarse la exterior 0  *********/
#[avr_device::interrupt(atmega328p)]
fn INT0() {
    if !es_rebote()   // Solo cambia cuando REBOTE es falso es decir ya se ha procesado el estado
    {
        let mut actual = ESTADO.load(Ordering::SeqCst);
        actual = actual + 1;
        if actual > 7 { actual = 0; }
        ESTADO.store(actual, Ordering::SeqCst);
        REBOTE.store(true, Ordering::SeqCst);   // Se debera poner a falso una vez se trate el estado.
    }
}

