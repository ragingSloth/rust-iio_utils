extern crate libc;
use libc::{c_char, c_int};

#[link(name = "libiio")]
extern {
    fn set_dev_paths(device_name: *mut c_char) -> c_int;
}

fn main(){
    unsafe {println!("your dir {}", set_dev_paths("ad9361-phy") as i16)}
}
