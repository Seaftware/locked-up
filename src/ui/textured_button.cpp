#include "ui/textured_button.hpp"

namespace Ui
{
    TexturedButton::TexturedButton(const std::string& text, const sf::Font& font,
        ButtonTextures textures, Ui::Button::Callback callback,
        sf::Vector2f position, Ui::Anchor origin, Ui::Anchor anchor)
        : Button(
        WidgetType::TexturedButton, text, font, callback, position,
        (sf::Vector2f) textures.default_texture.getSize(), ButtonColors(), origin, anchor
    ), textures(textures)
    {}

    const sf::Texture& TexturedButton::get_texture() const
    {
        if(activated)
            return textures.active_texture;
        else if(hovered)
            return textures.hover_texture;
        else
            return textures.default_texture;
    }
}