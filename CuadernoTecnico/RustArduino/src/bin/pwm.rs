/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Ejemplo de desarrollo en Arduino con el lenguage Rust.                                 *
 *               este ejemplo pretender mostrar el uso de los pines PWM                                 *
 *               Realizando un FADE  de dos LEDs cada uno en un Timer (d10 y d11)                       *
 *                                                                                                      *
 *  Historico:                                                                                          *
 *      Creación:  0.1.0 Abril 2024  FJRN                                                               *
 *                                                                                                      *
 ********************************************************************************************************/
#![no_std]           // No usa libreria estandard, sino la core al tratarse de embebido
#![no_main]          // No usa la funcion main como inicio

use arduino_hal::simple_pwm::*;
use panic_halt as _;    // Tratamiento de ecepciones


#[arduino_hal::entry]      // Punto de entrada del programa
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    // Definimos los pines PWM a utilizar
    //let timer0 = Timer0Pwm::new(dp.TC0, Prescaler::Prescale64);
    //let mut led5 = pins.d5.into_output().into_pwm(&timer0);
    //let mut led6 = pins.d6.into_output().into_pwm(&timer0);

    let timer1 = Timer1Pwm::new(dp.TC1, Prescaler::Prescale64);
    //let mut led9 = pins.d9.into_output().into_pwm(&timer1);
    let mut led10 = pins.d10.into_output().into_pwm(&timer1);

    let timer2 = Timer2Pwm::new(dp.TC2, Prescaler::Prescale64);
    //let mut led3 = pins.d3.into_output().into_pwm(&timer2);
    let mut led11 = pins.d11.into_output().into_pwm(&timer2);
  
    // Los habilitamos
    led10.enable();  
    led11.enable();  


    // Configuracion de consola
    //let mut serial = arduino_hal::default_serial!(dp, pins, 57600);
    //_ = ufmt::uwriteln!(serial, "Valor {}!",led10.get_max_duty());

    // Este loop seria la función loop() de un programa arduino normal.
    loop {
        for x in (0..=255).chain((0..=254).rev()) {
            led10.set_duty(x);
            led11.set_duty(x);
            arduino_hal::delay_ms(20);
        }
    }
}
