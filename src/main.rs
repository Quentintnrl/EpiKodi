use std::fs::File;
use std::io::Read;
use std::process::Command;

fn main() {
    let mut file = File::open("json/application.json").expect("File not found");
    let mut contents = String::new();
    file.read_to_string(&mut contents).expect("Failed to read file");

    let json_application: epikodi::application::application::JsonKodiApplication = serde_json::from_str(&contents).expect("Failed to parse JSON");
    let mut application: epikodi::application::application::KodiApplication = epikodi::application::application::KodiApplication::new(json_application);

    let output = Command::new("gnome-extensions")
        .arg("enable")
        .arg("hidetopbar@mathieu.bidon.ca")
        .output()
        .expect("Failed to execute command");

    if output.status.success() {
        println!("Command executed successfully.");
    } else {
        eprintln!("Error: {}", String::from_utf8_lossy(&output.stderr));
    }
    application.start();
    let output = Command::new("gnome-extensions")
        .arg("disable")
        .arg("hidetopbar@mathieu.bidon.ca")
        .output()
        .expect("Failed to execute command");

    if output.status.success() {
        println!("Command executed successfully.");
    } else {
        eprintln!("Error: {}", String::from_utf8_lossy(&output.stderr));
    }


        /*let main_window = WindowDesc::new(build_ui())
            .title("Image Display Example")
            .window_size((1920.0, 1080.0))
            .resizable(true)
            .show_titlebar(false);
        // Set the initial state of the application
        let initial_state = AppState {};
        // Launch the application
        AppLauncher::with_window(main_window)
            .launch(initial_state)
            .expect("Failed to launch application");*/
}

//a struct that implement druid
// a method where i send a page and it's display it
// add some data to the json and to the different struct that compose a page


/*use std::path::PathBuf;
use druid::{AppLauncher, Data, Lens, Widget, WidgetExt, WindowDesc, ImageBuf, Event, EventCtx, RenderContext, Env};
use druid::widget::{Container, SizedBox, Painter, Controller};
use image::GenericImageView;

#[derive(Clone, Data, Lens)]
struct AppState {
    is_hovered: bool,
}

impl AppState {
    // Function to load the image from the file path
    fn load_image(path: &str) -> ImageBuf {
        let image_data = load_image_from_path(path).expect("Failed to load image");
        image_data
    }
}

struct HoverController {
    height: f64,
    widht: f64
}

impl HoverController {
    pub fn new(image_height: f64, image_width: f64) -> HoverController {
        HoverController {
            height: image_height,
            widht: image_width,
        }
    }
}

impl<W: Widget<AppState>> Controller<AppState, W> for HoverController {
    fn event(&mut self, child: &mut W, ctx: &mut EventCtx, event: &Event, data: &mut AppState, env: &Env) {
        match event {
            Event::MouseMove(mouse_event) => {
                // Check if the mouse is inside or outside the widget's rect
                let rect = druid::Rect::from_origin_size((0.0, 0.0), (self.widht, self.height));
                if rect.contains(mouse_event.pos) {
                    data.is_hovered = true;  // Set the hover flag to true
                } else {
                    data.is_hovered = false; // Reset the hover flag if the mouse leaves
                }
                ctx.request_paint(); // Request a repaint on mouse movement
            }
            _ => {}
        }

        // Pass the event to the child widget
        child.event(ctx, event, data, env);
    }
}

fn build_ui() -> impl Widget<AppState> {
    // Load two images and get their dimensions
    let image1_path = "/assets/home/power.png";
    let image2_path = "/assets/home/power_over.png";

    let image1 = load_image_from_path(image1_path).unwrap();
    let image2 = load_image_from_path(image2_path).unwrap();

    // Get image dimensions
    let image1_dimensions = image1.size();
    let image2_dimensions = image2.size();

    let dimensions = if image1_dimensions == image2_dimensions {
        image1_dimensions  // Both images are assumed to be the same size, so we pick one
    } else {
        druid::Size::new(image1_dimensions.width.max(image2_dimensions.width), image1_dimensions.height.max(image2_dimensions.height))
    };

    println!("Dimensions: {:?}", dimensions);

    // Create a painter to switch between two images dynamically
    let painter = Painter::new(move |ctx, data: &AppState, _env| {
        let image = if data.is_hovered {
            image2.clone()  // Display the second image when hovered
        } else {
            image1.clone()  // Display the first image when not hovered
        };

        // Draw the image in the widget's rect using the image's original size
        let cairo_image = image.to_image(ctx.render_ctx);

        // Instead of using ctx.size(), use the dimensions of the image
        let rect: druid::kurbo::Rect = druid::Rect::from_origin_size((0.0, 0.0), (image.size().width as f64, image.size().height as f64));

        ctx.draw_image(&cairo_image, rect, druid::piet::InterpolationMode::Bilinear);
    });

    // Create the widget with hover detection and set the size to the dimensions of the image
    Container::new(SizedBox::new(painter).fix_size(dimensions.width as f64, dimensions.height as f64))
        .controller(HoverController::new(image2_dimensions.height, image2_dimensions.width))
}

fn main() {
    // Define the initial state
    let initial_state = AppState { is_hovered: false };

    // Create the window description
    let main_window = WindowDesc::new(build_ui()).title("Hover to Switch Images")
        .window_size((1920.0, 1080.0));

    // Launch the app
    AppLauncher::with_window(main_window)
        .launch(initial_state)
        .expect("Failed to launch application");
}

fn load_image_from_path(path: &str) -> Option<ImageBuf> {
    let path_str = format!("{}{}", std::env::current_dir().unwrap().to_str().unwrap(), path);
    println!("Path: {}", path_str);
    if !PathBuf::from(path_str.clone()).exists() {
        return None;
    }
    // Use the `image` crate to load the image from file
    let img = image::open(PathBuf::from(path_str)).ok()?;
    let img_data = img.to_rgba8();
    let (width, height) = img.dimensions();

    Some(ImageBuf::from_raw(
        img_data.into_raw(),
        druid::piet::ImageFormat::RgbaSeparate,
        width as usize,
        height as usize,
    ))
}*/
