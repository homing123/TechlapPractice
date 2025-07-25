#pragma once

#include "D3DUtil.h"
#include <directxtk/SimpleMath.h>
#include <map>
#include <vector>

using namespace DirectX::SimpleMath;
using namespace std;
enum EVertexElementType
{
	Position,
	UV,
	Color,
	Tangent,
};
struct FVertexElementInfo
{
	int ByteSize = 0;
	LPCSTR Semantic = nullptr;
	DXGI_FORMAT Format = DXGI_FORMAT_R32G32B32_FLOAT;
	FVertexElementInfo() = default;
	FVertexElementInfo(int byteSize, const LPCSTR semantic, DXGI_FORMAT format) : ByteSize(byteSize), Semantic(semantic), Format(format) {}
};
struct InputLayoutElementInfo
{
	LPCSTR Semantic = nullptr;
	int AlignedByteOffset = 0;
	DXGI_FORMAT Format = DXGI_FORMAT_R32G32B32_FLOAT;

	InputLayoutElementInfo(int alignedByteOffset, const FVertexElementInfo& vertexElementInfo)
		: AlignedByteOffset(alignedByteOffset), Semantic(vertexElementInfo.Semantic), Format(vertexElementInfo.Format) {}

};

struct FMeshData
{
public:
	static FMeshData CubeMeshData;
	static FMeshData QuadMeshData;
private:
	static map<EVertexElementType, FVertexElementInfo> VertexElementInfoMap;

private:
	vector<EVertexElementType> Elements;
	vector<float> VertexValues;
	vector<D3D11_INPUT_ELEMENT_DESC> InputElementDescs;
	vector<int32_t> Indices;
	int VertexByteSize = 0;
	int VertexCount = 0;
public:
	FMeshData(const vector<EVertexElementType>& elements, const vector<float>& vertexValues, const vector<int32_t>& indices) : Elements(elements), VertexValues(vertexValues), Indices(indices)
	{
		UINT curAlignedByteOffset = 0;
		int elementCount = Elements.size();
		for (int i = 0; i < elementCount; i++)
		{
			FVertexElementInfo& vertexElementInfo = VertexElementInfoMap[elements[i]];
			D3D11_INPUT_ELEMENT_DESC elementDesc = { vertexElementInfo.Semantic, 0, vertexElementInfo.Format, 0, curAlignedByteOffset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			InputElementDescs.emplace_back(elementDesc);
			curAlignedByteOffset += vertexElementInfo.ByteSize;
		}

		VertexByteSize = curAlignedByteOffset; //버텍스 하나당 float 갯수
		VertexCount = (VertexValues.size() << 2) / VertexByteSize;
	}

	const UINT GetVertexByteWidth() const
	{
		return VertexByteSize;
	}
	const UINT GetVertexCount() const
	{
		return VertexCount;
	}
	const UINT GetIndexCount() const
	{
		return Indices.size();
	}


	const vector<float>& GetVertexValues() const
	{
		return VertexValues;
	}
	const vector<D3D11_INPUT_ELEMENT_DESC>& GetInputElementDescs() const
	{
		return InputElementDescs;
	}
	const vector<int32_t> GetIndices() const
	{
		return Indices;
	}
};