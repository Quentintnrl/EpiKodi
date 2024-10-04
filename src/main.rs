use std::io::prelude::*;
use std::fs::File;

fn main() {
    // let mut file = File::open("tests/page/json/abstract_page.json").expect("File not found");
    // let mut contents = String::new();
    // file.read_to_string(&mut contents).expect("Failed to read file");

    // let json_page: epikodi::page::abstract_page::JsonPage = serde_json::from_str(&contents).expect("Failed to parse JSON");
    // let page: epikodi::page::abstract_page::Page = epikodi::page::abstract_page::Page::new(json_page);
    // page.println();

    let mut file = File::open("tests/application/json/application.json").expect("File not found");
    let mut contents = String::new();
    file.read_to_string(&mut contents).expect("Failed to read file");

    let json_application: epikodi::application::application::JsonKodiApplication = serde_json::from_str(&contents).expect("Failed to parse JSON");
    let mut application: epikodi::application::application::KodiApplication = epikodi::application::application::KodiApplication::new(json_application);
    application.println();
    application.start();
}
