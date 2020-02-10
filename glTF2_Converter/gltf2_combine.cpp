#include "gltf2_combine.h"

glTF2_Combine::glTF2_Combine(const QImage& roughness,
                             const QImage& metallic,
                             const QImage& ambientOcclusion)
{
    setImages(roughness,
              metallic,
              ambientOcclusion);
}

glTF2_Combine::glTF2_Combine(QImage &&roughness,
                             QImage &&metallic,
                             QImage &&ambientOcclusion)
{
    setImages(roughness,
              metallic,
              ambientOcclusion);
}

glTF2_Combine::~glTF2_Combine() = default;

QImage glTF2_Combine::combined()
{
    QImage out{ m_roughness.size(), QImage::Format_RGB32 };
    auto imageWidth = m_roughness.size().width();
    auto imageHeight = m_roughness.size().height();
    // TODO:
    // optimize
    for (int x = 0; x < imageWidth; x++)
    {
        for (int y = 0; y < imageHeight; y++)
        {
            QRgb pixel = qRgb(qGray(m_roughness.pixel(x, y)),
                              qGray(m_metallic.pixel(x, y)),
                              qGray(m_ambientOcclusion.pixel(x, y)));
            out.setPixel(x, y, pixel);
        }
    }
    return out;
}

void glTF2_Combine::checkImageValidty(const QImage& roughness,
                                      const QImage& metallic,
                                      const QImage& ambientOcclusion)
{
    if (!roughness.isGrayscale()) {
        throw std::invalid_argument("roughness is not grayscale!");
    }
    if (!metallic.isGrayscale()) {
        throw std::invalid_argument("metallic is not grayscale!");
    }
    if (!ambientOcclusion.isGrayscale()) {
        throw std::invalid_argument("ambientOcclusion is not grayscale!");
    }
    if (roughness.size() != metallic.size() ||
            metallic.size() != ambientOcclusion.size()) {
        throw std::invalid_argument("images are of diferent dimentions!");
    }
}

void glTF2_Combine::setImages(const QImage& roughness,
                              const QImage& metallic,
                              const QImage& ambientOcclusion)
{
    checkImageValidty(roughness,
                      metallic,
                      ambientOcclusion);
    m_roughness = roughness;
    m_metallic = metallic;
    m_ambientOcclusion = ambientOcclusion;
}

void glTF2_Combine::setImages(QImage &&roughness, QImage &&metallic, QImage &&ambientOcclusion)
{
    checkImageValidty(roughness,
                      metallic,
                      ambientOcclusion);
    m_roughness = std::move(roughness);
    m_metallic = std::move(metallic);
    m_ambientOcclusion = std::move(ambientOcclusion);
}
