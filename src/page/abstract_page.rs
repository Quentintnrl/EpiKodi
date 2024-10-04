// use std::sync::Arc;

use serde::Deserialize;
use serde::Serialize;

use crate::band::abstract_band::AbstractBand;
use crate::band::abstract_band::Band;
use crate::band::abstract_band::JsonBand;
use crate::button::abstract_button::AbstractButton;
use crate::logo::abstract_logo::AbstractLogo;
use crate::page_content::abstract_page_content::AbstractPageContent;
use crate::page_content::abstract_page_content::PageContent;
use crate::page_content::abstract_page_content::JsonPageContent;
use crate::page_content::page_content_part::PageContentPartTrait;


#[derive(Serialize, Deserialize, Debug)]
pub struct JsonPage {
    pub name: String,
    pub band: JsonBand,
    pub content: JsonPageContent,
    pub height: i64,
    pub width: i64,
}

pub trait AbstractPage {
	fn new(json_elem: JsonPage) -> Self;
    fn get_name(&self) -> String;
    fn get_band(&self) -> &Band;
    fn get_content(&self) -> &PageContent;
    fn get_hide(&self) -> bool;
    fn get_height(&self) -> i64;
    fn get_width(&self) -> i64;
    fn set_hide(&mut self, hide: bool);
    fn set_height(&mut self, height: i64);
    fn set_width(&mut self, width: i64);
    fn println(&self) {
        println!("Page {{");
        println!("\tPage name: {}", self.get_name());
        println!("\tPage hide: {}", self.get_hide());
        println!("\tPage height: {}", self.get_height());
        println!("\tPage width: {}", self.get_width());
        println!("\tBand: {{");
        println!("\t\tname: {}", self.get_band().get_name());
        println!("\t\theight: {}", self.get_band().get_height());
        println!("\t\twidth: {}", self.get_band().get_width());
        println!("\t\tbackground_color: {}", self.get_band().get_background_color());
        println!("\t\tLogo {{");
        println!("\t\t\theight: {}", self.get_band().get_logo().get_height());
        println!("\t\t\twidth: {}", self.get_band().get_logo().get_width());
        println!("\t\t}}");
        println!("\t\t[");
        for button_row in self.get_band().get_buttons() {
            println!("\t\t\t[");
            for button in button_row {
                println!("\t\t\t\t{{");
                println!("\t\t\t\t\tname: {}", button.get_name());
                println!("\t\t\t\t\ttext: {}", button.get_text());
                println!("\t\t\t\t\ttype: {}", button.get_type());
                println!("\t\t\t\t\tis_hovered: {}", button.get_is_hovered());
                println!("\t\t\t\t\thide: {}", button.get_hide());
                println!("\t\t\t\t\theight: {}", button.get_height());
                println!("\t\t\t\t\twidth: {}", button.get_width());
                if button.get_name() == button_row.last().unwrap().get_name() {
                    println!("\t\t\t\t}}");
                } else {
                    println!("\t\t\t\t}},");
                }
            }
            if std::ptr::eq(button_row, self.get_band().get_buttons().last().unwrap()) {
                println!("\t\t\t]");
            } else {
                println!("\t\t\t],");
            }
        }
        println!("\t\t]");
        println!("\t}}");
        println!("\tPageContent : {{");
        println!("\t\tname: {}", self.get_content().get_name());
        println!("\t\theight: {}", self.get_content().get_height());
        println!("\t\twidth: {}", self.get_content().get_width());
        println!("\t\t[");
        for page_content_part in self.get_content().get_page_content_parts() {
            println!("\t\t\t{{");
            println!("\t\t\t\tname: {}", page_content_part.get_name());
            println!("\t\t\t\tname_left_space: {}", page_content_part.get_name_left_space());
            println!("\t\t\t\tname_button_space: {}", page_content_part.get_name_button_space());
            println!("\t\t\t\tcurrent_button_pos: {}", page_content_part.get_current_button_pos());
            println!("\t\t\t\tbutton_space: {}", page_content_part.get_button_space());
            println!("\t\t\t\t[");
            for button in page_content_part.get_buttons() {
                println!("\t\t\t\t\t{{");
                println!("\t\t\t\t\t\tname: {}", button.get_name());
                println!("\t\t\t\t\t\ttext: {}", button.get_text());
                println!("\t\t\t\t\t\ttype: {}", button.get_type());
                println!("\t\t\t\t\t\tis_hovered: {}", button.get_is_hovered());
                println!("\t\t\t\t\t\thide: {}", button.get_hide());
                println!("\t\t\t\t\t\theight: {}", button.get_height());
                println!("\t\t\t\t\t\twidth: {}", button.get_width());
                //if is last
                if button.get_name() == page_content_part.get_buttons().last().unwrap().get_name() {
                    println!("\t\t\t\t\t}}");
                } else {
                    println!("\t\t\t\t\t}},");
                }
            }
            println!("\t\t\t\t]");
            println!("\t\t\t}}");
        }
        println!("\t\t]");
        println!("\t}}");
        println!("}}");
    }
    // fn update_next_page(&mut self);
    // fn get_next_page(&self) -> Arc<Page>;
}

pub struct Page {
    _name: String,
    _band : Band,
    _content: PageContent,
    _hide: bool,
    _height: i64,
    _width: i64,
    // _next_page: Arc<Page>,
}

impl AbstractPage for Page {
    fn new(json_elem: JsonPage) -> Self {
        Page {
            _name: json_elem.name,
            _band: Band::new(json_elem.band),
            _content: PageContent::new(json_elem.content),
            _hide: false,
            _height: json_elem.height,
            _width: json_elem.width,
            //_next_page: Arc::new(Nothing)
            // _next_page: Arc::new(Nothing),
        }
    }

    fn get_name(&self) -> String {
        self._name.clone()
    }

    fn get_band(&self) -> &Band {
        &self._band
    }

    fn get_content(&self) -> &PageContent {
        &self._content
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

    fn set_hide(&mut self, hide: bool) {
        self._hide = hide;
    }

    fn set_height(&mut self, height: i64) {
        self._height = height;
    }

    fn set_width(&mut self, width: i64) {
        self._width = width;
    }
    // fn update_next_page(&mut self) {
    //     self._next_page = self._band.get_next_page();
    // }
    // fn get_next_page(&self) -> Arc<Page> {
    //     self._next_page.clone()
    // }
}
