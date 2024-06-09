/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Ejemplo de desarrollo en Arduino con el lenguage Rust.                                 *
 *               este ejemplo pretender mostrar el uso de los pines de analogicos                       *
 *                                                                                                      *
 *  Historico:                                                                                          *
 *      Creación:  0.1.0 Abril 2024  FJRN                                                               *
 *                                                                                                      *
 ********************************************************************************************************/
#![no_std]           // No usa libreria estandard, sino la core al tratarse de embebido
#![no_main]          // No usa la funcion main como inicio

// use arduino_hal::prelude::*;
use panic_halt as _;    // Tratamiento de ecepciones
//use arduino_hal::adc;


#[arduino_hal::entry]      // Punto de entrada del programa
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    // Configuracion de consola
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);
     //_ = ufmt::uwriteln!(serial, "Se pulsa!");

    let mut adc = arduino_hal::Adc::new(dp.ADC, Default::default());

    let a2 = pins.a2.into_analog_input(&mut adc);

    loop {
        let valor = a2.analog_read(&mut adc);
        //let valor = adc.read_blocking(&a2);
        _ = ufmt::uwriteln!(serial, "Valor: {}",valor);

        arduino_hal::delay_ms(1000);
    }
}
