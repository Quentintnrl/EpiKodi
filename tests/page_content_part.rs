extern crate epikodi;
use std::io::Read;

use epikodi::button::abstract_button::AbstractButton;
use epikodi::button::abstract_button::Button;
use epikodi::page_content::page_content_part::PageContentPart;
use epikodi::page_content::page_content_part::JsonPageContentPart;
use epikodi::page_content::page_content_part::PageContentPartTrait;

fn cmp_buttons(first_button: &Button, second_button: &Button) {
    assert_eq!(first_button.get_name(), second_button.get_name());
    assert_eq!(first_button.get_text(), second_button.get_text());
    assert_eq!(first_button.get_type(), second_button.get_type());
    assert_eq!(first_button.get_is_hovered(), second_button.get_is_hovered());
    assert_eq!(first_button.get_hide(), second_button.get_hide());
    assert_eq!(first_button.get_height(), second_button.get_height());
    assert_eq!(first_button.get_width(), second_button.get_width());
}

#[test]

fn test_page_content() {
    let mut file = std::fs::File::open("tests/page_content_part/json/abstract_page_content_part.json").unwrap();
    let mut contents: String = String::new();
    file.read_to_string(&mut contents).unwrap();

    let json_page_content_part: JsonPageContentPart = serde_json::from_str(&contents).unwrap();
    let page_content_part: PageContentPart = PageContentPart::new(json_page_content_part);
    assert_eq!(page_content_part.get_name(), "Categories");
    assert_eq!(page_content_part.get_name_left_space(), 20);
    assert_eq!(page_content_part.get_name_button_space(), 30);
    assert_eq!(page_content_part.get_buttons().len(), 9);
    let mut test_button: Button = Button::new_empty();
    test_button.set_name("Genres".to_string());
    test_button.set_text("".to_string());
    test_button.set_type("to_page".to_string());
    test_button.set_is_hovered(false);
    test_button.set_hide(false);
    test_button.set_asset(None);
    test_button.set_over_asset(None);
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[0], &test_button);
    test_button.set_name("Titles".to_string());
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[1], &test_button);
    test_button.set_name("Years".to_string());
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[2], &test_button);
    test_button.set_name("Actors".to_string());
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[3], &test_button);
    test_button.set_name("Directors".to_string());
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[4], &test_button);
    test_button.set_name("Studios".to_string());
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[5], &test_button);
    test_button.set_name("Countries".to_string());
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[6], &test_button);
    test_button.set_name("Tags".to_string());
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[7], &test_button);
    test_button.set_name("Versions".to_string());
    test_button.set_height(50);
    test_button.set_width(50);
    cmp_buttons(&page_content_part.get_buttons()[8], &test_button);
    assert_eq!(page_content_part.get_current_button_pos(), 0);
    assert_eq!(page_content_part.get_button_space(), 50);
}