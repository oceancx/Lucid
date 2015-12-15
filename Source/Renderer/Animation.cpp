#include "Animation.h"


Animation::Animation(std::vector<AnimationData> &data) : m_Duration(1.0f)
{
	m_AnimationData = data;
}

std::string Animation::GetName()
{
    return m_Name;
}
std::shared_ptr<Texture2D> Animation::GetDiffuse()
{
    return m_Diffuse;
}
std::shared_ptr<Texture2D> Animation::GetSpecular()
{
    return m_Specular;
}
std::shared_ptr<Texture2D> Animation::GetNormal()
{
    return m_Normal;
}

void Animation::SetName(std::string name)
{
    m_Name = name;
}
void Animation::SetDuration(float duration)
{
	m_Duration = duration;
}
void Animation::SetDiffuse(std::shared_ptr<Texture2D> diffuse)
{
    m_Diffuse = diffuse;
}
void Animation::SetSpecular(std::shared_ptr<Texture2D> specular)
{
    m_Specular = specular;
}
void Animation::SetNormal(std::shared_ptr<Texture2D> normal)
{
    m_Normal = normal;
}

void Animation::Init(std::shared_ptr<Shader> shader)
{

}

void Animation::Normalize(int width, int height)
{
	for (auto it = m_AnimationData.begin(); it != m_AnimationData.end(); ++it)
	{
		it->XOffset = it->XOffset / width;
		it->YOffset = it->YOffset / height;
		it->Width   = it->Width / width;
		it->Height  = it->Height / height;
	}
}

void Animation::Update(float deltaTime)
{
	m_CurrentTime += deltaTime;
	m_CurrentTime = fmod(m_CurrentTime, m_Duration);
}

void Animation::ToShader(std::shared_ptr<Shader> shader)
{
	// calculate current frame
	float unit = m_CurrentTime / m_Duration;
	int nr_frames = m_AnimationData.size();
	int current_frame = static_cast<int>(unit * nr_frames);
	// send relevant animation data to shader
	shader->SetVector4f("animationData", m_AnimationData[current_frame].ToVec4(), true);
	// bind relevant sheets
	/*m_SpriteSheet_Diffuse.Bind(0); // will be done by Material
	m_SpriteSheet_Diffuse.Bind(1);
	m_SpriteSheet_Diffuse.Bind(2);*/
}
