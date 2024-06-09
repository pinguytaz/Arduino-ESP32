/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Scan de I2C para saber los dispositivos conectados a nuestro BUS I2C                   *
 *                                                                                                      *
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

    // Definimos el BUS en A4 y A5 indicando que ponga resistencia Pull_Up la propia placa.
    let mut i2c = arduino_hal::I2c::new(
        dp.TWI,
        pins.a4.into_pull_up_input(),
        pins.a5.into_pull_up_input(),
        50000,
     );

    _ = ufmt::uwriteln!(serial, "Inicio Test de direcciones!");

    //i2c.i2cdetect(&mut serial, arduino_hal::i2c::Direction::Write); 
    //i2c.i2cdetect(&mut serial, arduino_hal::i2c::Direction::Read);

    for direccion in 0x00..=0x7F {
        let (ah, al) = (u4_to_hex(direccion >> 4), u4_to_hex(direccion & 0xf));
        //_ = ufmt::uwriteln!(serial, "direccion {} 0x{}{}",direccion,ah,al);
        match i2c.ping_device(direccion,arduino_hal::i2c::Direction::Write) {
                Ok(true) => {
                    _ = ufmt::uwriteln!(serial, "Localizado Escritura {}(0x{}{})",direccion,ah,al);
                }
                Ok(false) => {
                    //_ = ufmt::uwriteln!(serial, "No encontrado W {}",direccion);
                }
                Err(e) => {
                    _ = ufmt::uwriteln!(serial, "ERROR {:?}",e);
                }
        }

        /*match i2c.ping_device(direccion,arduino_hal::i2c::Direction::Read) {
                Ok(true) => {
                    _ = ufmt::uwriteln!(serial, "Localizado Lectura {}(0x{}{})",direccion,ah,al);
                }
                Ok(false) => {
                    //_ = ufmt::uwriteln!(serial, "No encontrado L {}",direccion);
                }
                Err(e) => {
                    _ = ufmt::uwriteln!(serial, "ERROR {:?}",e);
                }
        }*/
    }
    _ = ufmt::uwriteln!(serial, "Finalización del test de direcciones!");

    loop {
        arduino_hal::delay_ms(1000);
    }
}

fn u4_to_hex(b: u8) -> char {
            match b {
                x if x < 0xa => (0x30 + x).into(),
                x if x < 0x10 => (0x57 + x).into(),
                _ => '?',
            }
}
