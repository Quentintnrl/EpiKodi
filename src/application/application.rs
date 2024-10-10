use serde::{Deserialize, Serialize};
use std::{io::Read, sync::Arc};

use crate::page::abstract_page::{AbstractPage, Page, JsonPage};
use crate::graphic::graphic::Graphic;

#[derive(Serialize, Deserialize, Debug)]
pub struct JsonKodiApplication {
    name: String,
    home_page_path : String,
    //modules
}

pub struct KodiApplication {
    pub name: String,
    _page_order : Vec<Arc<Page>>,
    _run : bool,
    _graphic: Graphic,
    //modules
}

impl KodiApplication {
    pub fn new(json_elem: JsonKodiApplication) -> Self {
        let path_str = format!("{}{}", std::env::current_dir().unwrap().to_str().unwrap(), json_elem.home_page_path);
        //print path
        let mut file = std::fs::File::open(path_str).expect("File not found");
        let mut contents = String::new();
        file.read_to_string(&mut contents).expect("Failed to read file");
        let json_page: JsonPage = serde_json::from_str(&contents).expect("Failed to parse JSON");
        let page: Page = Page::new(json_page);
        KodiApplication {
            name: json_elem.name,
            _page_order: vec![Arc::new(page)],
            _run: false,
            _graphic: Graphic::new(),
        }
    }
    pub fn start(& mut self) {
        self._run = true;
        let last_page = self._page_order.last().unwrap();
        //get the Page object
        let arc = last_page.clone();
        //get the page in thr Arc<Page> object
        self._graphic.display_page((*arc).clone());
        // while self._run {
        //     check if the current page has changed
        //     if (self._page_order.last().get_new_page() != None) {
        //         self._page_order.push((_page_order.last().get_new_page()));
        //     }
        //     handle events
        //     draw
        //     check other modules
        // }
    }
    pub fn println(&self) {
        println!("Application {{");
        println!("\tApplication name: {}", self.name);
        println!("\tPage order: [");
        for page in &self._page_order {
            println!("\t\t{{");
            page.println();
            //if lase page
            if Arc::ptr_eq(page, self._page_order.last().unwrap()) {
                println!("\t\t}}");
            } else {
                println!("\t\t}},");
            }
        }
        println!("\t]");
        println!("}}");
    }
}