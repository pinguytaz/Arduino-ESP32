/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Ejemplo de desarrollo en Arduino con el lenguage Rust.                                 *
 *               este ejemplo pretender mostrar el uso de los pines de digitales                        *
 *               tanto como entradas (boton) como salida los LEDs.                                               *
 *                                                                                                      *
 *                                                                                                      *
 *  Historico:                                                                                          *
 *      Creación:  0.1.0 Marzo 2024  FJRN                                                               *
 *                                                                                                      *
 ********************************************************************************************************/
#![no_std]           // No usa libreria estandard, sino la core al tratarse de embebido
#![no_main]          // No usa la funcion main como inicio

use panic_halt as _;    // Tratamiento de ecepciones


#[arduino_hal::entry]      // Punto de entrada del programa
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    //let mut led1 = pins.d12.into_output();  // Lo pone como salida
    let mut led1 = pins.d12.into_output_high();  // Salida y pone HIGH
    let mut led2 = pins.d11.into_output();
    let mut led3 = pins.d10.into_output();

    let boton = pins.d2;  // El boton es una entrada por defecto.

    // Configuracion de consola
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    // Este loop seria la función loop() de un programa arduino normal.
    loop {
        led3.toggle();   // El tercero siempre parpadea

        // Mira Boton
        if boton.is_high()   // El boton se activa a alto
        {
           led1.toggle();  // Cambia estado al primero
           led2.set_high(); // Se enciende el segundo
           _ = ufmt::uwriteln!(serial, "Se pulsa!");
        }
        else
        {
            led2.set_low(); // Lo apaga
        }
        arduino_hal::delay_ms(1000);
    }
}
