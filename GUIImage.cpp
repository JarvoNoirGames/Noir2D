#include "GUIImage.h"
#include <iostream>

Noir2D::GUIImage::GUIImage(const sf::Vector2f& position, const sf::Texture& texture, bool smooth) : GUIElement(position)
{
    _sprite.setTexture(texture);
    _sprite.setPosition(position);
    _originalSize = sf::Vector2f(texture.getSize());
    SetOriginalPosition(position);
    UpdateLayout();
}

void Noir2D::GUIImage::Draw(sf::RenderWindow& window)
{
    window.draw(_sprite);
}

void Noir2D::GUIImage::UpdateLayout()
{
    auto& res = ResolutionManager::GetInstance();
    float scaleX = res.GetScaleX();
    float scaleY = res.GetScaleY();
    sf::Vector2f scaledPosition = { GetOriginalPosition().x * scaleX, GetOriginalPosition().y * scaleY};
    sf::Vector2f scaledSize = { _originalSize.x * scaleX, _originalSize.y * scaleY };
    _sprite.setPosition(scaledPosition);
    sf::Vector2f textureSize = sf::Vector2f(_sprite.getTexture()->getSize());
    _sprite.setScale(scaledSize.x / textureSize.x, scaledSize.y / textureSize.y);
}

void Noir2D::GUIImage::SetSize(const sf::Vector2f& size)
{
    auto texSize = _sprite.getTexture()->getSize();
    _sprite.setScale(size.x / texSize.x, size.y / texSize.y);
}

void Noir2D::GUIImage::SetOpacity(float alpha)
{
    sf::Color color = _sprite.getColor();
    _sprite.setColor(sf::Color(color.r, color.g, color.b, static_cast<sf::Uint8>(alpha * 255)));
}

void Noir2D::GUIImage::SetPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}
