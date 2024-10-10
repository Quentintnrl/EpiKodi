use druid::widget::{Flex, Image, Padding, SizedBox};
use druid::{AppLauncher, Data, Lens, Widget, WidgetExt, WindowDesc};
use druid::piet::ImageBuf;
use image::GenericImageView;
use piet::{Color, UnitPoint};
use std::fs::File;
use std::io::Read;
use std::path::PathBuf; // For working with file paths
use std::process::Command;

#[derive(Clone, Data, Lens)]
struct AppState {
    // You can store other data related to your application here.
}

fn main() {
    let mut file = File::open("json/application.json").expect("File not found");
    let mut contents = String::new();
    file.read_to_string(&mut contents).expect("Failed to read file");

    let json_application: epikodi::application::application::JsonKodiApplication = serde_json::from_str(&contents).expect("Failed to parse JSON");
    let mut application: epikodi::application::application::KodiApplication = epikodi::application::application::KodiApplication::new(json_application);

/*    let output = Command::new("gnome-extensions")
        .arg("enable")
        .arg("hidetopbar@mathieu.bidon.ca")
        .output()
        .expect("Failed to execute command");

    if output.status.success() {
        println!("Command executed successfully.");
    } else {
        eprintln!("Error: {}", String::from_utf8_lossy(&output.stderr));
    }

        let main_window = WindowDesc::new(build_ui())
            .title("Image Display Example")
            .window_size((1920.0, 1080.0))
            .resizable(true)
            .show_titlebar(false);
        // Set the initial state of the application
        let initial_state = AppState {};
        // Launch the application
        AppLauncher::with_window(main_window)
            .launch(initial_state)
            .expect("Failed to launch application");
        let output = Command::new("gnome-extensions")
        .arg("disable")
        .arg("hidetopbar@mathieu.bidon.ca")
        .output()
        .expect("Failed to execute command");

    if output.status.success() {
        println!("Command executed successfully.");
    } else {
        eprintln!("Error: {}", String::from_utf8_lossy(&output.stderr));
    }*/
}

fn build_ui() -> impl Widget<AppState> {
    // Load logo
    let logo = load_image_from_path("/assets/home/logo.png").expect("Failed to load logo");

    // Load the first image from a file
    let image1 = load_image_from_path("/assets/home/movies.png").expect("Failed to load first image");

    // Load the second image from a file
    let image2 = load_image_from_path("/assets/home/tv_shows.png").expect("Failed to load second image");

    // Load the first image from a file
    let image3 = load_image_from_path("/assets/home/music.png").expect("Failed to load third image");

    // Load the second image from a file
    let image4 = load_image_from_path("/assets/home/music_videos.png").expect("Failed to load fourth image");

    // Load the first image from a file
    let image5 = load_image_from_path("/assets/home/tv.png").expect("Failed to load fift image");

    // Load the second image from a file
    let image6 = load_image_from_path("/assets/home/radio.png").expect("Failed to load sixth image");

    // Load the first image from a file
    let image7 = load_image_from_path("/assets/home/games.png").expect("Failed to seventh image");

    // Load the second image from a file
    let image8 = load_image_from_path("/assets/home/add_ons.png").expect("Failed to load eighth image");

    // Load the first image from a file
    let image9 = load_image_from_path("/assets/home/pictures.png").expect("Failed to load ninth image");

    // Load the second image from a file
    let image10 = load_image_from_path("/assets/home/videos.png").expect("Failed to load tenth image");

    // Load the first image from a file
    let image11 = load_image_from_path("/assets/home/favourites.png").expect("Failed to eleventh image");

    // Load the second image from a file
    let image12 = load_image_from_path("/assets/home/weather.png").expect("Failed to load twelfth image");

    //Load the power image from a file
    let power = load_image_from_path("/assets/home/power.png").expect("Failed to load power image");

    //Load the settings image from a file
    let settings = load_image_from_path("/assets/home/param.png").expect("Failed to load settings image");

    //Load the search image from a file
    let search = load_image_from_path("/assets/home/search.png").expect("Failed to load search image");

    // Create the Image widgets
    let logo_widget: SizedBox<AppState> = Image::new(logo.clone()).fix_size(460.0, 101.0); // Set specific width and height
    let power_widget: SizedBox<AppState> = Image::new(power).fix_size(115.0, 120.0); // Set specific width and height
    let settings_widget: SizedBox<AppState> = Image::new(settings).fix_size(115.0, 120.0); // Set specific width and height
    let search_widget: SizedBox<AppState> = Image::new(search).fix_size(115.0, 120.0); // Set specific width and height

    let image_widgets: Vec<SizedBox<AppState>> = vec! [
        Image::new(image1).fix_size(460.0, 100.0),
        Image::new(image2).fix_size(460.0, 100.0),
        Image::new(image3).fix_size(460.0, 100.0),
        Image::new(image4).fix_size(460.0, 100.0),
        Image::new(image5).fix_size(460.0, 100.0),
        Image::new(image6).fix_size(460.0, 100.0),
        Image::new(image7).fix_size(460.0, 100.0),
        Image::new(image8).fix_size(460.0, 100.0),
        Image::new(image9).fix_size(460.0, 100.0),
        Image::new(image10).fix_size(460.0, 100.0),
        Image::new(image11).fix_size(460.0, 100.0),
        Image::new(image12).fix_size(460.0, 100.0),
    ]
    .into_iter()
    .map(|img| SizedBox::new(img))
    .collect();

    let row = Flex::row()
        .with_child(Padding::new((0.0, 0.0, 0.0, 0.0), SizedBox::new(power_widget)))
        .with_spacer(57.5)
        .with_child(Padding::new((0.0, 0.0, 0.0, 0.0), SizedBox::new(settings_widget)))
        .with_spacer(57.5)
        .with_child(Padding::new((0.0, 0.0, 0.0, 0.0), SizedBox::new(search_widget)));

    // Create a vertical Flex container
    let mut column = Flex::column();

    // Add the logo
    column.add_child(Padding::new((0.0, 0.0, 0.0, 0.0), SizedBox::new(logo_widget)));

    //Add row
    column.add_child(Padding::new((0.0, 0.0, 0.0, 0.0), SizedBox::new(row)));

    // Add the images
    for img in image_widgets {
        column.add_child(Padding::new((0.0, 0.0, 0.0, 0.0), img));
    }

    // Align the entire column to the left and return it
    column.align_vertical(UnitPoint::TOP_LEFT)
    .background(Color::rgb8(0, 0, 0))
}

fn load_image_from_path(path: &str) -> Option<ImageBuf> {
    //print pwd
    // println!("Current directory: {:?}", std::env::current_dir().unwrap());
    // strcat the current dir with the path
    let path_str = format!("{}{}", std::env::current_dir().unwrap().to_str().unwrap(), path);
    //print path
    println!("Path: {}", path_str);
    //if path is wrong, return None
    if !PathBuf::from(path_str.clone()).exists() {
        return None;
    }
    // Use the `image` crate to load the image from file
    let img = image::open(PathBuf::from(path_str)).ok()?;

    // Convert the `image::DynamicImage` into a format usable by Druid's `ImageBuf`
    let img_data = img.to_rgba8();
    let (width, height) = img.dimensions();

    // Create the ImageBuf with the appropriate parameters
    Some(ImageBuf::from_raw(
        img_data.into_raw(),  // Raw pixel data
        druid::piet::ImageFormat::RgbaSeparate,      // Image format
        width as usize,     // Width
        height as usize,   // Height
    ))
}

//a struct that implement druid
// a method where i send a page and it's display it
// add some data to the json and to the different struct that compose a page
