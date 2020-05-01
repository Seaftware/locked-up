#pragma once

#include "item.hpp"
#include "widget.hpp"

namespace Ui
{
	class ItemWidget : public Widget
	{
	private:
		const sf::Texture* texture;
		Item item;

	public:
		ItemWidget(Item item, const sf::Texture& texture, sf::Vector2f position = { 0, 0 },
			Anchor origin = Anchor::TopLeft, Anchor anchor = Anchor::TopLeft);

		void set_texture(const sf::Texture& texture);

		const sf::Texture& get_texture() const;

		const Item& get_item() const;
	};
}