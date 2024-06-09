/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Ejemplo de desarrollo en Arduino con el lenguage Rust.                                 *
 *               Programación servomotor viendo el funcionamiento de los      *
 *               Timer/Counter                                                                          *
 *               Motor conectado al d10                                                                 *
 *    SM-S2309S: 5V, Rotación 180º Periodo PWM 50Hz Ancho de pulso 500us a 2000us                       *
 *    SG90: Ancho de pulso 500-2400us                                                                   *
 *    MG-996R                                                                                           *
 *       Velocidad 0,2s 5V y 0,16s 6V para 60 grados                                                    *
 *       Ciclo 20ms  Ancho pulso 600us a 2400 us                                                        *
 *                                                                                                      *
 *  Historico:                                                                                          *
 *      Creación:  0.1.0 Abril 2024  FJRN                                                               *
 *                                                                                                      *
 ********************************************************************************************************/
#![no_std]           // No usa libreria estandard, sino la core al tratarse de embebido
#![no_main]          // No usa la funcion main como inicio

use panic_halt as _;    // Tratamiento de ecepciones

#[arduino_hal::entry]      // Punto de entrada del programa
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    // - TC1 runs off a 250kHz clock, with 5000 counts per overflow => 50 Hz signal.
    // - Each count increases the duty-cycle by 4us.
    // - Use OC1A which is connected to D9 of the Arduino Uno.
    // Definimos el Timer/Counter que corresponda al pin
    // Prescalar 64
    // 16MHz / 64 = 250KHz    1/250*1000=4us
    // Queremos una señal de 50Hz  por lo tanto necesimos 5000 Ticks
    pins.d10.into_output();
    let tc1 = dp.TC1;    //TC0 (d6, d5) TC1 (d9, d10) TC2 (d11, d3)

    tc1.icr1.write(|w| w.bits(4999));    // Definimos los ticks necesarios en icr1

    tc1.tccr1a.write(|w| w.wgm1().bits(0b10).com1b().match_clear());  // Fast PWM(wgm1) y com1b OC1B Conectado
    tc1.tccr1b.write(|w| w.wgm1().bits(0b11).cs1().prescale_64());     

    // Configuracion de consola
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);
    //_ = ufmt::uwriteln!(serial, "Valor {}!",led10.get_max_duty());

    loop {
        for angulo in (0..=180).step_by(10) {
            _ = ufmt::uwriteln!(serial, "Angulo  {}", angulo);
            tc1.ocr1b.write(|w| w.bits(dutys(angulo)));
            arduino_hal::delay_ms(500);
        }
    }
}

//  Calculos realizados para MG  600us son 150 minimo  2400us son 600 maximo. 
//  Calculos realizados para SG90  500us son 125 minimo  2400us son 600 maximo. 
//  Calculos realizados para SM.S2309S  500us son 125 minimo  2000us son 500 maximo. 
fn dutys(angulo: i32) -> u16 {
   //return ((angulo * 450/180)+150).try_into().unwrap();
   //return ((angulo * 475/180)+125).try_into().unwrap();
   return ((angulo * 375/180)+125).try_into().unwrap();
}
