#pragma once
#include "Component.h"

using namespace Mydx;

namespace Mydx
{
    struct Mesh;
    struct Pass;
    struct Texture2D;
    struct SwapChainTexture2D;
    struct Viewport;
    class MeshRenderer :
        public Component
    {
    public:
        MeshRenderer();
        ~MeshRenderer();

        virtual void Init() override;
        virtual void Update(float delta) override;
        virtual void Render(float delta) override;
        virtual void Release() override;

        void SetMesh(Mesh* mesh);

        Mesh* GetMesh() const { return mMesh; }
        Pass* GetPass() const { return mPass; }

        void DrawForward(SwapChainTexture2D* target, Texture2D* depth, Viewport* viewport);
    private:
        void bindPass();
        void bindResources();

        void bindVertexShaderResources(ID3D11ShaderResourceView*const* shaderResources, unsigned int resourceCount);
        void bindPixelShaderResources(ID3D11ShaderResourceView* const* shaderResources, unsigned int resourceCount);
        
        void bindVertexConstBuffer(ID3D11Buffer* const* buffers, unsigned int bufferCount);
        void bindPixelConstBuffer(ID3D11Buffer* const* buffers, unsigned int bufferCount);

        Mesh* mMesh = nullptr;
        Pass* mPass = nullptr;

        ID3D11DeviceContext* mContext = nullptr;
    };

}