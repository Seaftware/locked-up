#pragma once

#include <functional>

#include "widget.hpp"
#include "text.hpp"

namespace Ui
{
    struct ButtonColors
    {
        sf::Color default_color = sf::Color::White;
        sf::Color hover_color = sf::Color::White;
        sf::Color active_color = sf::Color::White;
    };

    class Button : public Widget
    {
    protected:
        using Callback = std::function<void(Button&)>;

        bool activated = false;
        bool hovered = false;

        Button(WidgetType type, const std::string& text, const sf::Font& font, Callback callback,
            sf::Vector2f position = {0, 0}, sf::Vector2f size = {0, 0},
            ButtonColors colors = ButtonColors(), Anchor origin = Anchor::TopLeft,
            Anchor anchor = Anchor::TopLeft);

    private:
        Text text;
        ButtonColors colors;
        Callback callback;

    public:
        Button(const std::string& text, const sf::Font& font, Callback callback,
            sf::Vector2f position = {0, 0}, sf::Vector2f size = {0, 0},
            ButtonColors colors = ButtonColors(), Anchor origin = Anchor::TopLeft,
            Anchor anchor = Anchor::TopLeft);

        void handle_event(sf::Event event, sf::Vector2f mouse_pos) override;

        void set_text(Text text);

        const Text& get_text() const;

        void set_colors(ButtonColors colors);

        sf::Color get_color() const;

        void set_callback(Callback callback);
    };
}
