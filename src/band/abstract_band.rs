use crate::button::abstract_button::AbstractButton;
use crate::button::abstract_button::Button;
use crate::button::abstract_button::JsonButton;
use crate::logo::abstract_logo::Logo; //json button
use serde::Deserialize;
use serde::Serialize; //image in image
use crate::logo::abstract_logo::AbstractLogo; //abstract logo
use crate::logo::abstract_logo::JsonLogo; //json logo

#[derive(Serialize, Deserialize, Debug)]

pub struct JsonBand {
    pub name: String,
    pub height: i32,
    pub width: i32,
    pub background_color: String,
    pub logo: JsonLogo,
    pub buttons: Vec<Vec<JsonButton>>,
}

impl JsonBand {
    pub fn clone(&self) -> JsonBand {
        JsonBand {
            name: self.name.clone(),
            height: self.height,
            width: self.width,
            background_color: self.background_color.clone(),
            logo: self.logo.clone(),
            buttons: {
                let mut buttons = Vec::new();
                for button_row in &self.buttons {
                    let mut button_row_vec = Vec::new();
                    for button in button_row {
                        button_row_vec.push(button.clone());
                    }
                    buttons.push(button_row_vec);
                }
                buttons
            },
        }
    }
}

pub trait AbstractBand {
    fn new(json_band: JsonBand) -> Self;
    fn get_name(&self) -> &String;
    fn get_height(&self) -> i32;
    fn get_width(&self) -> i32;
    fn get_background_color(&self) -> &String;
    fn get_logo(&self) -> &Logo;
    fn get_buttons(&self) -> &Vec<Vec<Box<Button>>>;
    fn println(&self) {
        println!("Band {{");
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
        println!();
    }
}

pub struct Band {
    _name: String,
    _height: i32, //in px
    _width: i32, //in px
    _background_color: String, //hex color
    _logo: Option<Logo>, //logo image
    _buttons : Vec<Vec<Box<Button>>>,
}

impl AbstractBand for Band {
    fn new(json_band: JsonBand) -> Self {
        let mut buttons = Vec::new();
        for button_row in json_band.buttons {
            let mut button_row_vec = Vec::new();
            for json_button in button_row {
                let button = Button::new(json_button);
                button_row_vec.push(Box::new(button.unwrap()));
            }
            buttons.push(button_row_vec);
        }

        let logo : Option<Logo>;
        logo = Some(Logo::new(json_band.logo));

        Band {
            _name: json_band.name,
            _height: json_band.height,
            _width: json_band.width,
            _background_color: json_band.background_color,
            _logo: logo,
            _buttons: buttons,
        }
    }

    fn get_name(&self) -> &String {
        &self._name
    }

    fn get_height(&self) -> i32 {
        self._height
    }

    fn get_width(&self) -> i32 {
        self._width
    }

    fn get_background_color(&self) -> &String {
        &self._background_color
    }

    fn get_logo(&self) -> &Logo {
        self._logo.as_ref().unwrap()
    }

    fn get_buttons(&self) -> &Vec<Vec<Box<Button>>> {
        &self._buttons
    }
}
