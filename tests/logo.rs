extern crate epikodi;
use std::io::Read;

use epikodi::logo::abstract_logo::AbstractLogo;
use epikodi::logo::abstract_logo::JsonLogo;
use epikodi::logo::abstract_logo::Logo;

#[test]
fn test_logo() {
	let mut file = std::fs::File::open("tests/logo/json/abstract_logo.json").unwrap();
    let mut contents: String = String::new();
    file.read_to_string(&mut contents).unwrap();

    let json_logo: JsonLogo = serde_json::from_str(&contents).unwrap();
    let logo: Logo = Logo::new(json_logo);
    assert_eq!(logo.get_height(), 100.0);
    assert_eq!(logo.get_width(), 100.0);
}

