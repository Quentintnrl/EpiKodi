use druid::widget::{Align, Image, SizedBox};
use druid::{AppLauncher, Color, Data, Lens, Widget, WidgetExt, WindowDesc};
use druid::piet::ImageBuf;
use image::GenericImageView;
use piet::UnitPoint;
use std::path::PathBuf; // For working with file paths

#[derive(Clone, Data, Lens)]

fn build_ui_new(home_page: Page) -> impl Widget<AppState> {

}

struct AppState {
    // Any other state you want to track in the application
    //add exemple
}

pub struct Graphic {
    _window: WindowDesc<AppState>,
    _title: String,
    _height: f64,
    _width: f64,
    _current_page_name: String,
}

impl Graphic {
    pub fn new(title: &str, width: f64, height: f64, home_page: Page) -> Graphic {
        Graphic {
            _window: WindowDesc::new(build_ui_new(home_page))
                .window_size((width, height))
                .title(title)
                .resizable(true)
                .show_titlebar(false)
                .set_window_state(WindowState::Maximized),
            _title: title.to_string(),
            _height: height,
            _width: width,
        }
    }

    pub fn run(&self) {
        AppLauncher::with_window(self.window)
            .use_simple_logger()
            .launch(AppState {})
            .expect("launch failed");
    }
}
