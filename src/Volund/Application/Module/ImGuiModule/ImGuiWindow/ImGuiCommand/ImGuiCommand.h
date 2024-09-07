#pragma once

namespace Volund
{
	class ImGuiCommand
	{
	public:

		virtual void Execute(const std::string& id) = 0;

		virtual ~ImGuiCommand() = default;

	private:
	};

	class ImGuiResizeCommand : public ImGuiCommand
	{
	public:

		void Execute(const std::string& id) override;

		ImGuiResizeCommand(const Vec2& newSize);

	private:

		Vec2 m_NewSize = Vec2();
	};

	class ImGuiMoveCommand : public ImGuiCommand
	{
	public:

		void Execute(const std::string& id) override;

		ImGuiMoveCommand(const Vec2& newPosition);

	private:

		Vec2 m_NewPosition = Vec2();
	};
}