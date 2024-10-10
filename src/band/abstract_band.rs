use crate::button::abstract_button::AbstractButton;
use crate::button::abstract_button::Button;
use crate::button::abstract_button::JsonButton;
use crate::logo::abstract_logo::Logo; use piet::Color;
//json button
use serde::Deserialize;
use serde::Serialize; //image in image
use crate::logo::abstract_logo::AbstractLogo; //abstract logo
use crate::logo::abstract_logo::JsonLogo; //json logo

#[derive(Serialize, Deserialize, Debug)]

pub struct JsonRow {
    pub buttons_row: Vec<JsonButton>,
    pub spacer: f32,
    pub spacer_bool: bool,
}

impl JsonRow {
    pub fn clone(&self) -> JsonRow {
        JsonRow {
            buttons_row: {
                let mut buttons = Vec::new();
                for button in &self.buttons_row {
                    buttons.push(button.clone());
                }
                buttons
            },
            spacer: self.spacer,
            spacer_bool: self.spacer_bool,
        }
    }
}

#[derive(Serialize, Deserialize, Debug)]

pub struct JsonBand {
    pub name: String,
    pub height: f32,
    pub width: f32,
    pub background_r: i32,
    pub background_g: i32,
    pub background_b: i32,
    pub unit_point: String,
    pub logo: JsonLogo,
    pub row: JsonRow,
    pub buttons: Vec<JsonButton>,
}

impl JsonBand {
    pub fn clone(&self) -> JsonBand {
        JsonBand {
            name: self.name.clone(),
            height: self.height,
            width: self.width,
            background_r: self.background_r,
            background_g: self.background_g,
            background_b: self.background_b,
            unit_point: self.unit_point.clone(),
            logo: self.logo.clone(),
            row: self.row.clone(),
            buttons: {
                let mut buttons = Vec::new();
                for button in &self.buttons {
                    buttons.push(button.clone());
                }
                buttons
            },
        }
    }
}

pub trait AbstractBand {
    fn new(json_band: JsonBand) -> Self;
    fn get_name(&self) -> &String;
    fn get_height(&self) -> f32;
    fn get_width(&self) -> f32;
    fn get_background_color(&self) -> &Color;
    fn get_logo(&self) -> &Logo;
    fn get_row(&self) -> &Row;
    fn get_buttons(&self) -> &Vec<Box<Button>>;
    fn println(&self) {
        /*println!("Band {{");
        println!("\tname: {}", self.get_name());
        println!("\theight: {}", self.get_height());
        println!("\twidth: {}", self.get_width());
        println!("\tbackground_color: {}", self.get_background_color());
        println!("\tLogo {{");
        println!("\t\t Asset: {}", self.get_logo().get_asset().is_some());
        println!("\t\t Height: {}", self.get_logo().get_height());
        println!("\t\t Width: {}", self.get_logo().get_width());
        println!("\t}}");
        println!("\t[");
        let buttons = self.get_buttons();
        for button_row in buttons {
            println!("\t\t[");
            for button in button_row {
                println!("\t\t\t{{");
                println!("\t\t\t\tname: {}", button.get_name());
                println!("\t\t\t\ttext: {}", button.get_text());
                println!("\t\t\t\ttype: {}", button.get_type());
                println!("\t\t\t\tis_hovered: {}", button.get_is_hovered());
                println!("\t\t\t\thide: {}", button.get_hide());
                println!("\t\t\t\theight: {}", button.get_height());
                println!("\t\t\t\twidth: {}", button.get_width());
                if button_row.last().unwrap().get_name() == button.get_name() {
                    println!("\t\t\t}}");
                } else {
                    println!("\t\t\t}},");
                }
            }
            if buttons.last().unwrap().last().unwrap().get_name() == button_row.last().unwrap().get_name() {
                println!("\t\t]");
            } else {
                println!("\t\t],");
            }
        }
        println!("\t]");
        println!("}}");
        println!();*/
    }
    fn clone(&self) -> Self;
}

pub struct Row {
    _buttons_row: Vec<Box<Button>>,
    _spacer: f32,
    _spacer_bool: bool,
}

impl Row {
    pub fn new(json_row: JsonRow) -> Self {
        let mut buttons = Vec::new();
        for json_button in json_row.buttons_row {
            let button = Button::new(json_button);
            buttons.push(Box::new(button.unwrap()));
        }

        Row {
            _buttons_row: buttons,
            _spacer: json_row.spacer,
            _spacer_bool: json_row.spacer_bool,
        }
    }

    pub fn get_buttons_row(&self) -> &Vec<Box<Button>> {
        &self._buttons_row
    }

    pub fn get_spacer(&self) -> f32 {
        self._spacer
    }

    pub fn get_spacer_bool(&self) -> bool {
        self._spacer_bool
    }

    pub fn clone(&self) -> Self {
        let mut buttons: Vec<Box<Button>> = Vec::new();
        for button in &self._buttons_row {
            buttons.push(Box::new((**button).clone()));
        }
        Row {
            _buttons_row: buttons,
            _spacer: self._spacer,
            _spacer_bool: self._spacer_bool,
        }
    }
}

pub struct Band {
    _name: String,
    _height: f32, //in px
    _width: f32, //in px
    _background_color: Color, //rgb color
    _logo: Option<Logo>, //logo image
    _row: Row,
    _buttons : Vec<Box<Button>>,
}

impl AbstractBand for Band {
    fn new(json_band: JsonBand) -> Self {
        //add buttons vec
        let mut buttons = Vec::new();
        for json_button in json_band.buttons {
            let button = Button::new(json_button);
            buttons.push(Box::new(button.unwrap()));
        }
        let logo : Option<Logo>;
        logo = Some(Logo::new(json_band.logo));

        Band {
            _name: json_band.name,
            _height: json_band.height,
            _width: json_band.width,
            _background_color: Color::rgb8(json_band.background_r as u8, json_band.background_g as u8, json_band.background_b as u8),
            _logo: logo,
            _row: Row::new(json_band.row),
            _buttons: buttons,
        }
    }

    fn get_name(&self) -> &String {
        &self._name
    }

    fn get_height(&self) -> f32 {
        self._height
    }

    fn get_width(&self) -> f32 {
        self._width
    }

    fn get_background_color(&self) -> &Color {
        &self._background_color
    }

    fn get_logo(&self) -> &Logo {
        self._logo.as_ref().unwrap()
    }

    fn get_row(&self) -> &Row {
        &self._row
    }

    fn get_buttons(&self) -> &Vec<Box<Button>> {
        &self._buttons
    }

    fn clone(&self) -> Band {
        let mut buttons: Vec<Box<Button>> = Vec::new();
        for button in &self._buttons {
            buttons.push(Box::new((**button).clone()));
        }
        Band {
            _name: self._name.clone(),
            _height: self._height,
            _width: self._width,
            _background_color: self._background_color.clone(),
            _logo: Some(self._logo.as_ref().unwrap().clone()),
            _row: self._row.clone(),
            _buttons: buttons,
        }
    }
}
