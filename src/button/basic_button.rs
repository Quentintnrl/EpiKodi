use druid::ImageBuf; // ImageBuf from Druid for image handling
use std::path::PathBuf; // For working with file paths

use image::GenericImageView; // For loading images and getting dimensions
use std::option::Option; // Option type to handle the presence or absence of values
use std::boxed::Box; // Boxed closures for click and hover events
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug)]
pub struct Button {
    button_type: String,
    name: String,
    asset: String,
    asset_over: String,
    text: String,
    height: i64,
    width: i64,
}

impl Button {
    pub fn clone(&self) -> Button {
        Button {
            button_type: self.button_type.clone(),
            name: self.name.clone(),
            asset: self.asset.clone(),
            asset_over: self.asset_over.clone(),
            text: self.text.clone(),
            height: self.height,
            width: self.width,
        }
    }
}

pub struct AbstractButton {
    _name: String,
    _text: String,
    _on_click: Option<Box<dyn Fn()>>,
    _on_hover: Option<Box<dyn Fn()>>,
    _is_hovered: bool,
    _hide: bool,
    _asset: Option<ImageBuf>,
    _over_asset: Option<ImageBuf>,
    _height: i64,
    _width: i64,
}

impl AbstractButton {
    pub fn new(json_elem: Button) -> AbstractButton {
        AbstractButton {
            _text: json_elem.text,
            _name: json_elem.name,
            _on_click: None,
            _on_hover: None,
            _is_hovered: false,
            _hide: false,
            _asset: load_image_from_path(&json_elem.asset),
            _over_asset: load_image_from_path(&json_elem.asset_over),
            _height: 0,
            _width: 0,
        }
    }
}

fn load_image_from_path(path: &str) -> Option<ImageBuf> {
    // Use the `image` crate to load the image from file
    let img = image::open(PathBuf::from(path)).ok()?;

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
