use druid::ImageBuf; // ImageBuf from Druid for image handling
use std::path::PathBuf; // For working with file paths

use image::GenericImageView; // For loading images and getting dimensions
use std::option::Option; // Option type to handle the presence or absence of values
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug)]

pub struct JsonLogo {
    pub asset: String,
    pub height: f64,
    pub width: f64,
}

impl JsonLogo {
    pub fn clone(&self) -> JsonLogo {
        JsonLogo {
            asset: self.asset.clone(),
            height: self.height,
            width: self.width,
        }
    }
}

pub trait AbstractLogo {
    fn new(json_elem: JsonLogo) -> Self;
    fn get_asset(&self) -> Option<ImageBuf>;
    fn get_height(&self) -> f64;
    fn get_width(&self) -> f64;
    fn println(&self) {
        println!("Logo {{");
        println!("\tAsset: {}", self.get_asset().is_some());
        println!("\tHeight: {}", self.get_height());
        println!("\tWidth: {}", self.get_width());
        println!("}}");
        println!("");
    }
    fn clone(&self) -> Self;
}

pub struct Logo {
    _asset: Option<ImageBuf>,
    _height: f64,
    _width: f64,
}

impl AbstractLogo for Logo {
    fn new(json_elem: JsonLogo) -> Logo {
        let mut asset = None;
        if !json_elem.asset.is_empty() {
            asset = load_image_from_path(&json_elem.asset);
        }
        Logo {
            _asset: asset,
            _height: json_elem.height,
            _width: json_elem.width,
        }
    }

    fn get_asset(&self) -> Option<ImageBuf> {
        self._asset.clone()
    }

    fn get_height(&self) -> f64 {
        self._height
    }

    fn get_width(&self) -> f64 {
        self._width
    }

    fn clone(&self) -> Logo {
        Logo {
            _asset: self._asset.clone(),
            _height: self._height,
            _width: self._width,
        }
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
