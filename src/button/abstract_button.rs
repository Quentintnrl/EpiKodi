use druid::ImageBuf; // ImageBuf from Druid for image handling
use std::path::PathBuf; // For working with file paths

use image::GenericImageView; // For loading images and getting dimensions
use std::option::Option; // Option type to handle the presence or absence of values
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug)]
pub struct JsonButton {
    button_type: String,
    name: String,
    asset: String,
    asset_over: String,
    text: String,
    height: f64,
    width: f64,
    hide: bool,
}

impl JsonButton {
    pub fn clone(&self) -> JsonButton {
        JsonButton {
            button_type: self.button_type.clone(),
            name: self.name.clone(),
            asset: self.asset.clone(),
            asset_over: self.asset_over.clone(),
            text: self.text.clone(),
            height: self.height,
            width: self.width,
            hide: self.hide,
        }
    }
}

pub trait AbstractButton {
    fn new_empty() -> Button;
    fn new(json_elem: JsonButton) -> Result<Self, String> where Self: Sized;
    fn get_name(&self) -> String;
    fn get_text(&self) -> String;
    fn get_type(&self) -> String;
    fn get_is_hovered(&self) -> bool;
    fn get_hide(&self) -> bool;
    fn get_asset(&self) -> Option<ImageBuf>;
    fn get_over_asset(&self) -> Option<ImageBuf>;
    fn get_height(&self) -> f64;
    fn get_width(&self) -> f64;
    fn println(&self) {
        println!("Button {{");
        println!("\tname: {}", self.get_name());
        println!("\ttext: {}", self.get_text());
        println!("\ttype: {}", self.get_type());
        println!("\tis_hovered: {}", self.get_is_hovered());
        println!("\thide: {}", self.get_hide());
        println!("\theight: {}", self.get_height());
        println!("\twidth: {}", self.get_width());
        println!("}}");
        println!();
    }
    fn set_name(&mut self, name: String);
    fn set_text(&mut self, text: String);
    fn set_type(&mut self, button_type: String);
    fn set_is_hovered(&mut self, is_hovered: bool);
    fn set_hide(&mut self, hide: bool);
    fn set_asset(&mut self, asset: Option<ImageBuf>);
    fn set_over_asset(&mut self, asset_over: Option<ImageBuf>);
    fn set_height(&mut self, height: f64);
    fn set_width(&mut self, width: f64);
}

pub struct Button {
    _name: String,
    _text: String,
    _type_: String,
    _is_hovered: bool,
    _hide: bool,
    _asset: Option<ImageBuf>,
    _asset_over: Option<ImageBuf>,
    _height: f64,
    _width: f64,
}

impl AbstractButton for Button {
    fn new_empty() -> Button {
        Button {
            _name: "".to_string(),
            _text: "".to_string(),
            _type_: "".to_string(),
            _is_hovered: false,
            _hide: false,
            _asset: None,
            _asset_over: None,
            _height: 0.0,
            _width: 0.0,
        }
    }

    fn new(json_elem: JsonButton) -> Result<Button, String> {
        let asset = load_image_from_path(&json_elem.asset)
            .ok_or_else(|| format!("Asset not found: {}", json_elem.asset))?;
        let asset_over = load_image_from_path(&json_elem.asset_over)
            .ok_or_else(|| format!("Asset over not found: {}", json_elem.asset_over))?;

        Ok(Button {
            _name: json_elem.name,
            _text: json_elem.text,
            _type_: json_elem.button_type,
            _is_hovered: false,
            _hide: json_elem.hide,
            _asset: Some(asset),
            _asset_over: Some(asset_over),
            _height: json_elem.height,
            _width: json_elem.width,
        })
    }

    fn get_name(&self) -> String {
        self._name.clone()
    }

    fn get_text(&self) -> String {
        self._text.clone()
    }

    fn get_type(&self) -> String {
        self._type_.clone()
    }

    fn get_is_hovered(&self) -> bool {
        self._is_hovered
    }

    fn get_hide(&self) -> bool {
        self._hide
    }

    fn get_asset(&self) -> Option<ImageBuf> {
        self._asset.clone()
    }

    fn get_over_asset(&self) -> Option<ImageBuf> {
        self._asset_over.clone()
    }

    fn get_height(&self) -> f64 {
        self._height
    }

    fn get_width(&self) -> f64 {
        self._width
    }

    fn set_name(&mut self, name: String) {
        self._name = name;
    }

    fn set_text(&mut self, text: String) {
        self._text = text;
    }

    fn set_type(&mut self, button_type: String) {
        self._type_ = button_type;
    }

    fn set_is_hovered(&mut self, is_hovered: bool) {
        self._is_hovered = is_hovered;
    }

    fn set_hide(&mut self, hide: bool) {
        self._hide = hide;
    }

    fn set_asset(&mut self, asset: Option<ImageBuf>) {
        self._asset = asset;
    }

    fn set_over_asset(&mut self, asset_over: Option<ImageBuf>) {
        self._asset_over = asset_over;
    }

    fn set_height(&mut self, height: f64) {
        self._height = height;
    }

    fn set_width(&mut self, width: f64) {
        self._width = width;
    }

    fn println(&self) {
        std::println!("Button {{");
        std::println!("\tname: {}", self.get_name());
        std::println!("\ttext: {}", self.get_text());
        std::println!("\ttype: {}", self.get_type());
        std::println!("\tis_hovered: {}", self.get_is_hovered());
        std::println!("\thide: {}", self.get_hide());
        std::println!("\theight: {}", self.get_height());
        std::println!("\twidth: {}", self.get_width());
        std::println!("}}");
        std::println!();
    }
}

fn load_image_from_path(path: &str) -> Option<ImageBuf> {
    //print pwd
    // println!("Current directory: {:?}", std::env::current_dir().unwrap());
    // strcat the current dir with the path
    let path_str = format!("{}{}", std::env::current_dir().unwrap().to_str().unwrap(), path);
    //print path
    println!("Path: {}", path_str);
    //if path is wrong, return None
    if !PathBuf::from(path_str.clone()).exists() {
        return None;
    }
    // Use the `image` crate to load the image from file
    let img = image::open(PathBuf::from(path_str)).ok()?;

    // Convert the `image::DynamicImage` into a format usable by Druid's `ImageBuf`
    let img_data = img.to_rgba8();
    let (width, height) = img.dimensions();

    // Create the ImageBuf with the appropriate parameters
    Some(ImageBuf::from_raw(
        img_data.into_raw(),  // Raw pixel data
        druid::piet::ImageFormat::RgbaSeparate,      // Image format
        width as usize,     // Width
        height as usize,   // Height
    ))
}
