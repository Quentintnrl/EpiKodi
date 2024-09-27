mod button {
    pub mod basic_button;
}
use button::basic_button::AbstractButton; // Use the struct
use button::basic_button::Button; // Use the struct

use serde::{Deserialize, Serialize};
use std::fs; // For file operations

// use basic_button::AbstractButton; // Use the struct


#[derive(Serialize, Deserialize, Debug)]
struct ButtonGroup {
    buttons: Vec<Vec<Button>>,
}

fn main() -> std::result::Result<(), Box<dyn std::error::Error>> {
    println!("Hello, world!");
    // let button: AbstractButton = AbstractButton::new("./json/buttons/home_page.json".to_string());
    let json_string = fs::read_to_string("./json/buttons/home_page.json")?;

    // Deserialize the JSON string into a MyData struct
    let data: ButtonGroup = serde_json::from_str(&json_string)?;

    let _test_button = AbstractButton::new(data.buttons[0][0].clone());
    Ok(())
}
