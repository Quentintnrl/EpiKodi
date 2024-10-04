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
    height: i64,
    width: i64,
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
    fn new(json_elem: JsonButton) -> Result<Self, String> where Self: Sized;
    fn get_name(&self) -> String;
    fn get_text(&self) -> String;
    fn get_type(&self) -> String;
    fn get_is_hovered(&self) -> bool;
    fn get_hide(&self) -> bool;
    fn get_asset(&self) -> Option<ImageBuf>;
    fn get_over_asset(&self) -> Option<ImageBuf>;
    fn get_height(&self) -> i64;
    fn get_width(&self) -> i64;
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
}

pub struct Button {
    _name: String,
    _text: String,
    _type_: String,
    _is_hovered: bool,
    _hide: bool,
    _asset: Option<ImageBuf>,
    _asset_over: Option<ImageBuf>,
    _height: i64,
    _width: i64,
}

impl AbstractButton for Button {
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

    fn get_height(&self) -> i64 {
        self._height
    }

    fn get_width(&self) -> i64 {
        self._width
    }
}

fn load_image_from_path(path: &str) -> Option<ImageBuf> {
    //print pwd
    // println!("Current directory: {:?}", std::env::current_dir().unwrap());
    // strcat the current dir with the path
    let path_str = format!("{}{}", std::env::current_dir().unwrap().to_str().unwrap(), path);
    //print path
    // println!("Path: {}", path_str);
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
