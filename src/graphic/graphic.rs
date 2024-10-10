use druid::widget::{Container, Controller, Flex, Image, Padding, Painter, SizedBox};
use druid::piet::RenderContext;
use druid::{AppLauncher, Color, Env, Event, EventCtx, Lens, Widget, WidgetExt, WindowDesc, WindowState};
use piet::{ImageBuf, UnitPoint};

use crate::band::abstract_band::{AbstractBand, Band};
use crate::button::abstract_button::AbstractButton;
use crate::logo::abstract_logo::AbstractLogo;
use crate::page::abstract_page::{AbstractPage, Page}; // For working with file paths

fn build_ui(image1: ImageBuf, image2: ImageBuf, index: usize) -> impl Widget<AppState> {
    // Get image dimensions
    let image1_dimensions = image1.size();
    let image2_dimensions = image2.size();

    let dimensions = if image1_dimensions == image2_dimensions {
        image1_dimensions  // Both images are assumed to be the same size, so we pick one
    } else {
        druid::Size::new(image1_dimensions.width.max(image2_dimensions.width), image1_dimensions.height.max(image2_dimensions.height))
    };

    // Create a painter to switch between two images dynamically
    let painter = Painter::new(move |ctx, data: &AppState, _env| {
        let image = if data.hovered_images[index] {
            image2.clone()  // Display the second image when hovered
        } else {
            image1.clone()  // Display the first image when not hovered
        };

        // Draw the image in the widget's rect using the image's original size
        let cairo_image = image.to_image(ctx.render_ctx);

        let rect = druid::Rect::from_origin_size((0.0, 0.0), (image.size().width as f64, image.size().height as f64));

        ctx.draw_image(&cairo_image, rect, druid::piet::InterpolationMode::Bilinear);
    });

    // Create the widget with hover detection and set the size to the dimensions of the image
    Container::new(SizedBox::new(painter).fix_size(dimensions.width as f64, dimensions.height as f64))
        .controller(HoverController::new(index, image2_dimensions.height, image2_dimensions.width))
}

fn create_band_widget(band: Band) -> impl Widget<AppState> {
    let logo_asset = band.get_logo().get_asset().unwrap();
    let logo_widget: SizedBox<AppState> = Image::new(logo_asset.clone()).fix_size(band.get_logo().get_width(), band.get_logo().get_height());

    let mut row_widget = Flex::row();
    let mut image_index = 0;  // Initialize a global index tracker

    // Process buttons in the row
    for button in band.get_row().get_buttons_row() {
        if button.get_hide() {
            continue;
        }
        let button_widget = build_ui(button.get_asset().unwrap(), button.get_over_asset().unwrap(), image_index);
        image_index += 1;  // Increment the index after each button
        row_widget = row_widget.with_child(button_widget);

        if band.get_row().get_spacer_bool() {
            row_widget = row_widget.with_spacer(band.get_row().get_spacer() as f64);
        }
    }

    let buttons = band.get_buttons();
    let mut column = Flex::column();
    column.add_child(Padding::new((0.0, 0.0, 0.0, 0.0), logo_widget));
    column.add_child(Padding::new((0.0, 0.0, 0.0, 0.0), row_widget));

    // Process buttons in the column
    for button in buttons {
        if button.get_hide() {
            continue;
        }
        column.add_child(build_ui(button.get_asset().unwrap(), button.get_over_asset().unwrap(), image_index));
        image_index += 1;  // Increment the index after each button
    }

    column.align_vertical(UnitPoint::TOP_LEFT)
        .background(Color::rgb8(0, 0, 0))
}



fn build_ui_new(page: Page) -> impl Widget<AppState> {
    let band_widget = create_band_widget(page.get_band().clone());
    band_widget
}

#[derive(Clone, Lens)]
struct AppState {
    hovered_images: Vec<bool>,  // One boolean per image
}

impl druid::Data for AppState {
    fn same(&self, other: &Self) -> bool {
        self.hovered_images == other.hovered_images
    }
}

struct HoverController {
    index: usize,  // Index of the image this controller is responsible for
    height: f64,
    width: f64,
}

impl HoverController {
    pub fn new(index: usize, image_height: f64, image_width: f64) -> HoverController {
        HoverController {
            index,
            height: image_height,
            width: image_width,
        }
    }
}

impl<W: Widget<AppState>> Controller<AppState, W> for HoverController {
    fn event(&mut self, child: &mut W, ctx: &mut EventCtx, event: &Event, data: &mut AppState, env: &Env) {
        match event {
            Event::MouseMove(mouse_event) => {
                // Check if the mouse is inside or outside the widget's rect
                let rect = druid::Rect::from_origin_size((0.0, 0.0), (self.width, self.height));
                if rect.contains(mouse_event.pos) {
                    data.hovered_images[self.index] = true;  // Set the hover flag for this image
                } else {
                    data.hovered_images[self.index] = false; // Reset the hover flag if the mouse leaves
                }
                ctx.request_paint(); // Request a repaint on mouse movement
            }
            _ => {}
        }

        // Pass the event to the child widget
        child.event(ctx, event, data, env);
    }
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

    fn display(&self, window: WindowDesc<AppState>, initial_state: AppState) {
        // Launch the app with the provided window and initial state
        AppLauncher::with_window(window)
            .launch(initial_state)
            .expect("launch failed");
    }

    pub fn display_page(&self, page: Page) {
        let window = self.create_window(page.clone(), 1080.0, 1920.0, "Kodi".to_string());
        self.display(window, AppState { hovered_images: vec![false; page.get_band().get_buttons().len() + page.get_band().get_row().get_buttons_row().len()] });
    }
}
