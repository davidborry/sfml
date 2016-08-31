#include "../../headers/sound/SoundPlayer.hpp"

namespace{
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

SoundPlayer::SoundPlayer() :
mSoundBuffers(),
mSounds()
{
	mSoundBuffers.load(Resources::SoundEffects::AlliedGunfire, "Resources/sounds/AlliedGunfire.wav");
	mSoundBuffers.load(Resources::SoundEffects::EnemyGunfire, "Resources/sounds/EnemyGunfire.wav");
	mSoundBuffers.load(Resources::SoundEffects::Explosion1, "Resources/sounds/Explosion1.wav");
	mSoundBuffers.load(Resources::SoundEffects::Explosion2, "Resources/sounds/Explosion2.wav");
	mSoundBuffers.load(Resources::SoundEffects::LaunchMissile, "Resources/sounds/LaunchMissile.wav");
	mSoundBuffers.load(Resources::SoundEffects::Button, "Resources/sounds/Button.wav");
	mSoundBuffers.load(Resources::SoundEffects::CollectPickup, "Resources/sounds/CollectPickup.wav");

}

void SoundPlayer::play(Resources::SoundEffects::ID effect){
	play(effect, getListenerPosition());
}

void SoundPlayer::play(Resources::SoundEffects::ID effect, sf::Vector2f position){
	mSounds.push_back(sf::Sound());
	sf::Sound& sound = mSounds.back();

	sound.setBuffer(mSoundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();

}

sf::Vector2f SoundPlayer::getListenerPosition() const{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}

void SoundPlayer::removeStoppedSounds(){
	mSounds.remove_if([](const sf::Sound& s) {
		return s.getStatus() == sf::Sound::Stopped;
	});
}

void SoundPlayer::setListenerPosition(sf::Vector2f position){
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}