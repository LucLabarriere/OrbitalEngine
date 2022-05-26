#include "Tools.h"
#include "OrbitalEngine/Graphics/TextureManager.h"

Tools::Tools()
	: m_texture(Orbital::TextureManager::Get("Icons"))
	, m_ratio((float)TEXTURE_ICON_SIZE / (float)m_texture.lock()->getWidth())
{

}

bool Tools::RenderIconButton(TextureIconIndex iconIndex)
{
	return ImGui::ImageButton(
		(void*)(intptr_t)s_instance->m_texture.lock()->getRendererId(),
		ImVec2(16, 16),
		ImVec2(s_instance->m_ratio * (float)iconIndex, 0),
		ImVec2(s_instance->m_ratio * ((float)iconIndex + 1), 1)
	);
}

void Tools::RenderIcon(TextureIconIndex iconIndex)
{
	ImGui::Image(
		(void*)(intptr_t)s_instance->m_texture.lock()->getRendererId(),
		ImVec2(16, 16),
		ImVec2(s_instance->m_ratio * (float)iconIndex, 0),
		ImVec2(s_instance->m_ratio * ((float)iconIndex + 1), 1)
	);
}