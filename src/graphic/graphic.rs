use druid::widget::{Flex, Image, Padding, SizedBox};
use druid::{AppLauncher, Color, Data, Lens, Widget, WidgetExt, WindowDesc, WindowState};
use piet::UnitPoint;

use crate::band::abstract_band::{AbstractBand, Band};
use crate::button::abstract_button::AbstractButton;
use crate::logo::abstract_logo::AbstractLogo;
use crate::page::abstract_page::{AbstractPage, Page}; // For working with file paths

fn create_band_widget(band: Band) -> impl Widget<AppState> {
    let logo_asset = band.get_logo().get_asset().unwrap();
    let logo_widget: SizedBox<AppState> = Image::new(logo_asset.clone()).fix_size(band.get_logo().get_width(), band.get_logo().get_height());

    let mut row_widget = Flex::row();
    for button in band.get_row().get_buttons_row() {
        if button.get_hide() {
            continue;
        }
        let button_widget: SizedBox<AppState> = Image::new(button.get_asset().unwrap().clone()).fix_size(button.get_width(), button.get_height());
        row_widget = row_widget.with_child(button_widget);
        if band.get_row().get_spacer_bool() {
            row_widget = row_widget.with_spacer(band.get_row().get_spacer() as f64);
        }
    }
    let buttons = band.get_buttons();
    let mut column = Flex::column();
    column.add_child(Padding::new((0.0, 0.0, 0.0, 0.0), logo_widget));
    column.add_child(Padding::new((0.0, 0.0, 0.0, 0.0), row_widget));
    for button in buttons {
        if button.get_hide() {
            continue;
        }
        column.add_child(Padding::new((0.0, 0.0, 0.0, 0.0), SizedBox::new(Image::new(button.get_asset().unwrap().clone()).fix_size(button.get_width(), button.get_height()))));
    }
    column.align_vertical(UnitPoint::TOP_LEFT)
        .background(Color::rgb8(0, 0, 0))
}


fn build_ui_new(page: Page) -> impl Widget<AppState> {
    let band_widget = create_band_widget(page.get_band().clone());
    band_widget
}

#[derive(Clone, Data, Lens)]

struct AppState {
    // Any other state you want to track in the application
    //add exemple
}

pub struct Graphic {
}

impl Graphic {
    pub fn new() -> Graphic {
        Graphic {}
    }

    fn create_window(&self, page: Page, height: f64, width: f64, title: String) -> WindowDesc<AppState> {
        WindowDesc::new(build_ui_new(page))
            .window_size((width, height))
            .title(title)
            .resizable(true)
            .show_titlebar(false)
            .set_window_state(WindowState::Maximized)
    }

    fn display(&self, window: WindowDesc<AppState>) {
        AppLauncher::with_window(window)
            .launch(AppState {})
            .expect("launch failed");
    }

    pub fn display_page(&self, page: Page) {
        let window = self.create_window(page, 1080.0, 1920.0, "Kodi".to_string());
        self.display(window);
    }
}
