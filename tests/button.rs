extern crate epikodi;
use std::io::Read;

use epikodi::button::abstract_button::AbstractButton;
use epikodi::button::abstract_button::JsonButton;
use epikodi::button::abstract_button::Button;

#[test]
fn test_button() {
    let mut file = std::fs::File::open("tests/button/json/abstract_button.json").unwrap();
    let mut contents: String = String::new();
    file.read_to_string(&mut contents).unwrap();

    let json_button: JsonButton = serde_json::from_str(&contents).unwrap();
    let button: Button = Button::new(json_button).unwrap();
    assert_eq!(button.get_name(), "button");
    assert_eq!(button.get_text(), "god bless me");
    assert_eq!(button.get_type(), "test");
    assert_eq!(button.get_is_hovered(), false);
    assert_eq!(button.get_hide(), false);
    assert_eq!(button.get_height(), 50.0);
    assert_eq!(button.get_width(), 50.0);
}
