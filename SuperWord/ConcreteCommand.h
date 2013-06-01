#pragma once

#include "Composite.h"
#include "Command.h"
#include "NavigateWnd.h"

namespace comp
{
    namespace cmd
    {

        class SeriesCommand : public Component, public Command
        {
        public:
            virtual bool CanAddChild(const Composite * pChild) const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
			virtual bool Configure(const std::string& str);
			virtual std::string GetConfiguration() const;
            virtual bool Execute(NavigateWnd * pWnd) const;
        private:
            virtual Component * CreateObject() const;

			std::string m_remark;
        };

        class RandomCommand : public Component, public Command
        {
        public:
            virtual bool CanAddChild(const Composite * pChild) const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Execute(NavigateWnd * pWnd) const;
        private:
            virtual Component * CreateObject() const;
        };

        class IfCommand : public Component, public Command
        {
        public:
            virtual bool CanAddChild(const Composite * pChild) const;
            virtual bool HaveRoom() const;
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Execute(NavigateWnd * pWnd) const;
        private:
            virtual Component * CreateObject() const;
        };

        class TimerCommand : public Component, public Command
        {
        public:
            TimerCommand();
            virtual bool CanAddChild(const Composite * pChild) const;
            virtual bool HaveRoom() const;
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Execute(NavigateWnd * pWnd) const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
        private:
            virtual Component * CreateObject() const;

            unsigned long m_interval;
			size_t m_repeat_time;
			bool m_global;
        };

        class HotkeyCommand : public Component, public Command
        {
        public:
            HotkeyCommand();
            virtual bool CanAddChild(const Composite * pChild) const;
            virtual bool HaveRoom() const;
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Execute(NavigateWnd * pWnd) const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
        private:
            virtual Component * CreateObject() const;
            ACCEL m_acl;
            std::string m_strAccel;
			bool m_global;
        };

        class MoveWordCommand : public Leaf, public Command
        {
        public:
            MoveWordCommand();
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
            virtual bool Execute(NavigateWnd * pWnd) const;
            static const char ms_arrOp[][32];
        private:
            virtual Leaf * CreateObject() const;
            NavigateWnd::MoveOp m_op;
        };

        class SetColorCommand : public Leaf, public Command
        {
        public:
            SetColorCommand();
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
            virtual bool Execute(NavigateWnd * pWnd) const;
        private:
            virtual Leaf * CreateObject() const;

            std::string m_color_element;
            unsigned long m_cr;
        };

		class OpenDlgCommand : public Leaf, public Command
		{
		public:
			OpenDlgCommand();
			virtual bool CheckValid() const;
			virtual std::string GetName() const;
			virtual std::string GetDescription() const;
			virtual bool Configure(const std::string& str);
			virtual std::string GetConfiguration() const;
			virtual bool Execute(NavigateWnd * pWnd) const;
		private:
			virtual Leaf * CreateObject() const;

			std::string m_dlg_name;
		};

		class ShowElementCommand : public Leaf, public Command
		{
		public:
			ShowElementCommand();
			virtual bool CheckValid() const;
			virtual std::string GetName() const;
			virtual std::string GetDescription() const;
			virtual bool Configure(const std::string& str);
			virtual std::string GetConfiguration() const;
			virtual bool Execute(NavigateWnd * pWnd) const;
		private:
			virtual Leaf * CreateObject() const;

			std::string m_visual_element;
			bool m_show;
		};

		class SetWordTypeCommand : public Leaf, public Command
		{
		public:
			SetWordTypeCommand();
			virtual bool CheckValid() const;
			virtual std::string GetName() const;
			virtual std::string GetDescription() const;
			virtual bool Configure(const std::string& str);
			virtual std::string GetConfiguration() const;
			virtual bool Execute(NavigateWnd * pWnd) const;
		private:
			virtual Leaf * CreateObject() const;

			std::string m_word_type;
			NavigateWnd::SetTypeStyle m_style;
		};

		class MiscCommand : public Leaf, public Command
		{
		public:
			MiscCommand();
			virtual bool CheckValid() const;
			virtual std::string GetName() const;
			virtual std::string GetDescription() const;
			virtual bool Configure(const std::string& str);
			virtual std::string GetConfiguration() const;
			virtual bool Execute(NavigateWnd * pWnd) const;
		private:
			virtual Leaf * CreateObject() const;

			std::string m_cmd;
		};

		class LoadCompCommand : public Leaf, public Command
		{
		public:
			LoadCompCommand();
			virtual bool CheckValid() const;
			virtual std::string GetName() const;
			virtual std::string GetDescription() const;
			virtual bool Configure(const std::string& str);
			virtual std::string GetConfiguration() const;
			virtual bool Execute(NavigateWnd * pWnd) const;
		private:
			virtual Leaf * CreateObject() const;

			std::string m_composite_file;
		};
    }
}