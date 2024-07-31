#pragma once

namespace Grape
{

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Grape::ShaderDataType::Float:		return 4;
		case Grape::ShaderDataType::Float2:		return 4 * 2;
		case Grape::ShaderDataType::Float3:		return 4 * 3;
		case Grape::ShaderDataType::Float4:		return 4 * 4;
		case Grape::ShaderDataType::Int:		return 4;
		case Grape::ShaderDataType::Int2:		return 4 * 2;
		case Grape::ShaderDataType::Int3:		return 4 * 3;
		case Grape::ShaderDataType::Int4:		return 4 * 4;
		case Grape::ShaderDataType::Mat3:		return 4 * 3 * 3;
		case Grape::ShaderDataType::Mat4:		return 4 * 4 * 4;		
		}
		GP_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case Grape::ShaderDataType::Float:		return 1;
			case Grape::ShaderDataType::Float2:		return 2;
			case Grape::ShaderDataType::Float3:		return 3;
			case Grape::ShaderDataType::Float4:		return 4;
			case Grape::ShaderDataType::Int:		return 1;
			case Grape::ShaderDataType::Int2:		return 2;
			case Grape::ShaderDataType::Int3:		return 3;
			case Grape::ShaderDataType::Int4:		return 4;
			case Grape::ShaderDataType::Mat3:		return 3 * 3;
			case Grape::ShaderDataType::Mat4:		return 4 * 4;
			default:
				break;
			}
			GP_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_elements(elements)
		{
			CalculateOffsetsAndStride();
		}
		const std::vector<BufferElement>& GetElements() const { return m_elements; }
		const uint32_t GetStride() const { return m_stride; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }


	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_stride = 0;
			for (auto& ele : m_elements)
			{
				ele.Offset = offset;
				offset += ele.Size;
				m_stride += ele.Size;
			}
		}

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		static VertexBuffer* Create(float* vertices, uint32_t size);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
	};
}