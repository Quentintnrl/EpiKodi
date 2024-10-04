use serde::Deserialize;
use serde::Serialize;

use crate::button::abstract_button::AbstractButton;
use crate::button::abstract_button::Button;
use crate::button::abstract_button::JsonButton;

#[derive(Debug, Serialize, Deserialize)]

pub struct JsonPageContentPart {
    pub name: String,
    pub name_left_space: i32,
    pub name_button_space: i32,
    pub buttons: Vec<JsonButton>,
    pub current_button_pos: i32,
    pub button_space: i32,
}

impl JsonPageContentPart {
    pub fn clone(&self) -> JsonPageContentPart {
        JsonPageContentPart {
            name: self.name.clone(),
            name_left_space: self.name_left_space,
            name_button_space: self.name_button_space,
            buttons: {
                let mut buttons = Vec::new();
                for button in &self.buttons {
                    buttons.push(button.clone());
                }
                buttons
            },
            current_button_pos: self.current_button_pos,
            button_space: self.button_space,
        }
    }
}

pub trait PageContentPartTrait {
    fn new(json_elem: JsonPageContentPart) -> Self;
    fn get_name(&self) -> &String;
    fn get_name_left_space(&self) -> i32;
    fn get_name_button_space(&self) -> i32;
    fn get_buttons(&self) -> &Vec<Button>;
    fn get_current_button_pos(&self) -> i32;
    fn get_button_space(&self) -> i32;
    fn set_name(&mut self, name: String);
    fn set_name_left_space(&mut self, name_left_space: i32);
    fn set_name_button_space(&mut self, name_button_space: i32);
    fn set_buttons(&mut self, buttons: Vec<Button>);
    fn set_current_button_pos(&mut self, current_button_pos: i32);
    fn set_button_space(&mut self, button_space: i32);
    fn add_button(&mut self, button: Button);
    fn remove_button(&mut self, button: Button);
    fn println(&self) {
        println!("PageContentPart {{");
        println!("\tname: {}", self.get_name());
        println!("\tname_left_space: {}", self.get_name_left_space());
        println!("\tname_button_space: {}", self.get_name_button_space());
        println!("\tcurrent_button_pos: {}", self.get_current_button_pos());
        println!("\tbutton_space: {}", self.get_button_space());
        println!("\tbuttons: [");
        for button in self.get_buttons() {
            println!("\t\t{{");
            println!("\t\t\tname: {}", button.get_name());
            println!("\t\t\ttext: {}", button.get_text());
            println!("\t\t\ttype: {}", button.get_type());
            println!("\t\t\tis_hovered: {}", button.get_is_hovered());
            println!("\t\t\thide: {}", button.get_hide());
            println!("\t\t\twidth: {}", button.get_width());
            println!("\t\t\theight: {}", button.get_height());
            //if is last
            if button.get_name() == self.get_buttons().last().unwrap().get_name() {
                println!("\t\t}}");
            } else {
                println!("\t\t}},");
            }
        }
        println!("\t]");
        println!("}}");
    }
}

pub struct PageContentPart {
    _name: String,
    _name_left_space: i32,
    _name_button_space: i32,
    _buttons: Vec<Button>,
    _current_button_pos: i32,
    _button_space: i32,
}

impl PageContentPartTrait for PageContentPart {
    fn new(json_elem: JsonPageContentPart) -> PageContentPart {
        let mut buttons = Vec::new();
        for json_button in json_elem.buttons {
            //create button and throw error if button has an error
            let button = Button::new(json_button);
            //check the string
            if button.is_err() {
                panic!("Error: {}", button.err().unwrap());
            }
            buttons.push(button.unwrap());
        }
        PageContentPart {
            _name: json_elem.name,
            _name_left_space: json_elem.name_left_space,
            _name_button_space: json_elem.name_button_space,
            _buttons: buttons,
            _current_button_pos: json_elem.current_button_pos,
            _button_space: json_elem.button_space,
        }
    }

    fn get_name(&self) -> &String {
        &self._name
    }

    fn get_name_left_space(&self) -> i32 {
        self._name_left_space
    }

    fn get_name_button_space(&self) -> i32 {
        self._name_button_space
    }

    fn get_buttons(&self) -> &Vec<Button> {
        &self._buttons
    }

    fn get_current_button_pos(&self) -> i32 {
        self._current_button_pos
    }

    fn get_button_space(&self) -> i32 {
        self._button_space
    }

    fn set_name(&mut self, name: String) {
        self._name = name;
    }

    fn set_name_left_space(&mut self, name_left_space: i32) {
        self._name_left_space = name_left_space;
    }

    fn set_name_button_space(&mut self, name_button_space: i32) {
        self._name_button_space = name_button_space;
    }

    fn set_buttons(&mut self, buttons: Vec<Button>) {
        self._buttons = buttons;
    }

    fn set_current_button_pos(&mut self, current_button_pos: i32) {
        self._current_button_pos = current_button_pos;
    }

    fn set_button_space(&mut self, button_space: i32) {
        self._button_space = button_space;
    }

    fn add_button(&mut self, button: Button) {
        self._buttons.push(button);
    }

    fn remove_button(&mut self, button: Button) {
        let mut index = 0;
        for i in 0..self._buttons.len() {
            if self._buttons[i].get_name() == button.get_name() {
                index = i;
                break;
            }
        }
        self._buttons.remove(index);
    }
}
