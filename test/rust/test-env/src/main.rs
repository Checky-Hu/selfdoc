use std::env;

fn main() {
    println!("TARGET={:?}", env::var("TARGET").ok());
}
