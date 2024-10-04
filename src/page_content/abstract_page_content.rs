use serde::Deserialize;
use serde::Serialize;

use crate::button::abstract_button::AbstractButton;
// use crate::page::Page;
// use crate::page::JsonPage;
use crate::page_content::page_content_part::JsonPageContentPart;
use crate::page_content::page_content_part::PageContentPart;
use super::page_content_part::PageContentPartTrait;

#[derive(Debug, Serialize, Deserialize)]

pub struct JsonPageContent {
    pub name: String,
    pub height: i64,
    pub width: i64,
    pub page_content_parts: Vec<JsonPageContentPart>,
}

pub trait AbstractPageContent {
    fn new(json_elem: JsonPageContent) -> Self;
    fn get_name(&self) -> String;
    fn get_hide(&self) -> bool;
    fn get_height(&self) -> i64;
    fn get_width(&self) -> i64;
    fn get_page_content_parts(&self) -> &Vec<PageContentPart>;
    fn set_hide(&mut self, hide: bool);
    fn set_height(&mut self, height: i64);
    fn set_width(&mut self, width: i64);
    fn update_next_page(&mut self);
    // fn get_next_page(&self) -> Arc<Page>;
    fn println(&self) {
        println!("PageContent {{");
        println!("\tname: {}", self.get_name());
        println!("\thide: {}", self.get_hide());
        println!("\theight: {}", self.get_height());
        println!("\twidth: {}", self.get_width());
        println!("\t[");
        for page_content_part in self.get_page_content_parts() {
            println!("\t\t{{");
            println!("\t\t\tname: {}", page_content_part.get_name());
            println!("\t\t\tname_left_space: {}", page_content_part.get_name_left_space());
            println!("\t\t\tname_button_space: {}", page_content_part.get_name_button_space());
            println!("\t\t\tcurrent_button_pos: {}", page_content_part.get_current_button_pos());
            println!("\t\t\tbutton_space: {}", page_content_part.get_button_space());
            println!("\t\t\t[");
            for button in page_content_part.get_buttons() {
                println!("\t\t\t\t{{");
                println!("\t\t\t\t\tname: {}", button.get_name());
                println!("\t\t\t\t\ttext: {}", button.get_text());
                println!("\t\t\t\t\ttype: {}", button.get_type());
                println!("\t\t\t\t\tis_hovered: {}", button.get_is_hovered());
                println!("\t\t\t\t\thide: {}", button.get_hide());
                println!("\t\t\t\t\theight: {}", button.get_height());
                println!("\t\t\t\t\twidth: {}", button.get_width());
                //if is last
                if button.get_name() == page_content_part.get_buttons().last().unwrap().get_name() {
                    println!("\t\t\t\t}}");
                } else {
                    println!("\t\t\t\t}},");
                }
            }
            println!("\t\t\t]");
        }
        println!("\t\t}}");
        println!("\t]");
        println!("}}");
    }
}

impl JsonPageContent {
    pub fn clone(&self) -> JsonPageContent {
        JsonPageContent {
            name: self.name.clone(),
            height: self.height,
            width: self.width,
            page_content_parts: {
                let mut page_content_parts = Vec::new();
                for page_content_part in &self.page_content_parts {
                    page_content_parts.push(page_content_part.clone());
                }
                page_content_parts
            }
        }
    }
}

pub struct PageContent {
    _name: String,
    _hide: bool,
    _height: i64,
    _width: i64,
    _page_content_parts: Vec<PageContentPart>,
}

impl AbstractPageContent for PageContent {
    fn new(json_elem: JsonPageContent) -> Self {
        let mut page_content_parts: Vec<PageContentPart> = Vec::new();
        for json_elem in json_elem.page_content_parts {
            page_content_parts.push(PageContentPart::new(json_elem));
        }

        PageContent {
            _name: json_elem.name,
            _hide: false,
            _height: json_elem.height,
            _width: json_elem.width,
            _page_content_parts: page_content_parts,
        }
    }

    fn get_name(&self) -> String {
        self._name.clone()
    }

    fn get_hide(&self) -> bool {
        self._hide
    }

    fn get_height(&self) -> i64 {
        self._height
    }

    fn get_width(&self) -> i64 {
        self._width
    }

    fn get_page_content_parts(&self) -> &Vec<PageContentPart> {
        &self._page_content_parts
    }

    fn set_hide(&mut self, hide: bool) {
        self._hide = hide;
    }

    fn set_height(&mut self, height: i64) {
        self._height = height;
    }

    fn set_width(&mut self, width: i64) {
        self._width = width;
    }

    fn update_next_page(&mut self) {
        //TODO
    }

    // fn get_next_page(&self) -> Arc<Page> {
    //     self._next_page.clone()
    // }
}
