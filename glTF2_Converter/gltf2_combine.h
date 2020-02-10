#ifndef GLTF2_COMBINE_H
#define GLTF2_COMBINE_H

#include <QImage>

class glTF2_Combine
{
public:
    glTF2_Combine(const QImage& roughness,
                  const QImage& metallic,
                  const QImage& ambientOcclusion);
    glTF2_Combine(QImage&& roughness,
                  QImage&& metallic,
                  QImage&& ambientOcclusion);
    virtual ~glTF2_Combine();
    QImage combined();

private:
    void setImages(const QImage& roughness,
                   const QImage& metallic,
                   const QImage& ambientOcclusion);
    void setImages(QImage&& roughness,
                   QImage&& metallic,
                   QImage&& ambientOcclusion);
    void checkImageValidty(const QImage& roughness,
                           const QImage& metallic,
                           const QImage& ambientOcclusion);

    QImage m_roughness;
    QImage m_metallic;
    QImage m_ambientOcclusion;
};

#endif // GLTF2_COMBINE_H
