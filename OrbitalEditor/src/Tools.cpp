#include "Tools.h"
#include "OrbitalEngine/Graphics/TextureManager.h"

Tools::Tools()
	: mTexture(Orbital::TextureManager::Get("Icons"))
	, mRatio((float)TEXTURE_ICON_SIZE / (float)mTexture.lock()->GetWidth())
{

}

bool Tools::RenderIconButton(TextureIconIndex iconIndex)
{
	return ImGui::ImageButton(
		(void*)(intptr_t)sInstance->mTexture.lock()->GetRendererId(),
		ImVec2(16, 16),
		ImVec2(sInstance->mRatio * (float)iconIndex, 0),
		ImVec2(sInstance->mRatio * ((float)iconIndex + 1), 1)
	);
}

void Tools::RenderIcon(TextureIconIndex iconIndex)
{
	ImGui::Image(
		(void*)(intptr_t)sInstance->mTexture.lock()->GetRendererId(),
		ImVec2(16, 16),
		ImVec2(sInstance->mRatio * (float)iconIndex, 0),
		ImVec2(sInstance->mRatio * ((float)iconIndex + 1), 1)
	);
}