/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Ejemplo de desarrollo en Arduino con el lenguage Rust.                                 *
 *               Programación de un sonar con el sensor HC-SR04                                         *
 *               Ejemplo de utilización de un Timer/Counter como contador de tiempo.                    *
 *               Se conecta a los pines d2 para lanzar el Triger y d3 recoge el ECHO                    *
 *               Definimos un timre/Counter TC1 (16 bits) para ver el tiempo de llegada del ECHO        *
 *               HC-SR04                                                                                *
 *                   Rango: 2cm a 400cm con un angulo de 15 grados. Resolución unos 0.3cm               *
 *                   Señal de triger sera un pulso de 10 us                                             *
 *                   Tiempo espera entre una medida mas de 50ms
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

    // Configuracion de consola
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    let mut trig = pins.d2.into_output();    // Digital de salida lanza el Triger
    let echo = pins.d3; // Pin de entrada del ECHO.prescale_64());     

    // Definimos el Timer TC1 a Prescale 64 lo que define que cada Tick son 4 us.
    //  Contador es de 16 bits por lo tanto agunata hasta 262 ms
    let timer1 = dp.TC1;
    timer1.tccr1b.write(|w| w.cs1().prescale_64()); // Definimos el prescaler

    'l_principal: loop {
        // Espera de 100ms antes de lanzar el siguiente TRIGER aprobechamos el contador y no usamos delay_ms
        timer1.tcnt1.write(|w| w.bits(0));
        while timer1.tcnt1.read().bits() < 25000 {}

        //arduino_hal::delay_ms(5000);  // Espera de tiempo con Delay para debuger y no calcular los ticks.

        // Lanzamos ECHO, segun documentación HC-SR04  mantenemos el pin 10us en alto
        trig.set_low();
        arduino_hal::delay_us(4);  // Aseguramos bajo durante 4us.
        trig.set_high();
        arduino_hal::delay_us(10); // 10us de alto como indica el DataSheet.
        trig.set_low();

        // Esperamos a que se envie la rafaga y levante ECHO.
        while echo.is_low() {}

        //Reiniciamos el timer para la medida de la distancia y esperamos la bajada de ECHO para calcular la distancia
        timer1.tcnt1.write(|w| w.bits(0));
        while echo.is_high() {}

        let contador = timer1.tcnt1.read().bits().saturating_mul(4); // se multiplica por 4 para saber los us que ha tardado.
        let distancia = match contador {
            u16::MAX => {   // Sobrepasa contador
                _ = ufmt::uwriteln!( &mut serial, "No se ha detectado obtaculo");
                continue 'l_principal;   // Volvemos al principio del bucle infinito.
            },
            _ => contador / 58,
        };

        _ = ufmt::uwriteln!( &mut serial, "La distancia al obtaculo esta en {} cms aproximadamente", distancia);
    }
}
