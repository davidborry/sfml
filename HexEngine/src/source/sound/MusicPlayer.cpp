#include "../../headers/sound/MusicPlayer.hpp"

MusicPlayer::MusicPlayer() :
mMusic(),
mFilenames(),
mVolume(100.f)
{
	mFilenames[Resources::Musics::MenuTheme] = "Resources/musics/MenuTheme.ogg";
	mFilenames[Resources::Musics::MissionTheme] = "Resources/musics/MissionTheme.ogg";
}

void MusicPlayer::play(Resources::Musics::ID theme){
	std::string filename = mFilenames[theme];

	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}


void MusicPlayer::stop(){
	mMusic.stop();
}

void MusicPlayer::setPaused(bool paused){
	if (paused)
		mMusic.pause();
	else
		mMusic.play();
}

void MusicPlayer::setVolume(float volume){
	mVolume = volume;
}