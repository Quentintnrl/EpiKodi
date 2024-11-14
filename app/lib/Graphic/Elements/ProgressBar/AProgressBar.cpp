#include "AProgressBar.hpp"

AProgressBar::AProgressBar(const std::size_t progress, const std::size_t maxProgress) : _progress(progress), _maxProgress(maxProgress) {}

const void AProgressBar::setProgress(const std::size_t progress) {
    _progress = progress;
}

const void AProgressBar::setMaxProgress(const std::size_t maxProgress) {
    _maxProgress = maxProgress;
}

const std::size_t AProgressBar::getProgress() const {
    return _progress;
}

const std::size_t AProgressBar::getMaxProgress() const {
    return _maxProgress;
}