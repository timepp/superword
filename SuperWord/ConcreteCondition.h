#pragma once

#include "Composite.h"
#include "Condition.h"
#include "Word.h"
#include "LibSrc/greta/regexpr2.h"

#include <string>
#include <vector>

namespace comp
{
    namespace cond
    {

        class AndCondition : public Component, public Condition
        {
        public:
            virtual bool CanAddChild(const Composite * pChild) const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Meet(const void * pTestee) const;
        private:
            virtual Component * CreateObject() const;
        };

        class OrCondition : public Component, public Condition
        {
        public:
            virtual bool CanAddChild(const Composite * pChild) const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Meet(const void * pTestee) const;
        private:
            virtual Component * CreateObject() const;
        };

        class NotCondition : public Component, public Condition
        {
        public:
            virtual bool CanAddChild(const Composite * pChild) const;
            virtual bool HaveRoom() const;
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Meet(const void * pTestee) const;
        private:
            virtual Component * CreateObject() const;
        };

        class WordCondition : public Leaf, public Condition
        {
        public:
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
            virtual bool Meet(const void * pTestee) const;
        private:
            virtual Leaf * CreateObject() const;

            std::string m_match_str;
            regex::rpattern m_match_pat;
        };

        class MeaningCondition : public Leaf, public Condition
        {
        public:
            MeaningCondition();
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
            virtual bool Meet(const void * pTestee) const;
        private:
            virtual Leaf * CreateObject() const;

            std::string m_match_str;
            regex::rpattern m_match_pat;
            bool m_match_detail_meaning;
        };

        class PhoneticCondition : public Leaf, public Condition
        {
        public:
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
            virtual bool Meet(const void * pTestee) const;
        private:
            virtual Leaf * CreateObject() const;

            std::string m_match_str;
            regex::rpattern m_match_pat;
        };

        class AccesstimeCondition : public Leaf, public Condition
        {
        public:
            AccesstimeCondition();
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
            virtual bool Meet(const void * pTestee) const;
        private:
            virtual Leaf * CreateObject() const;

            bool m_use_relative_time;
            long m_relative_time;
            bool m_min_time_valid;
            bool m_max_time_valid;
            time_t m_min_time;
            time_t m_max_time;
        };

        class ClassCondition : public Leaf, public Condition
        {
        public:
			virtual bool CheckValid() const;
            virtual std::string GetName() const;
            virtual std::string GetDescription() const;
            virtual bool Configure(const std::string& str);
            virtual std::string GetConfiguration() const;
            virtual bool Meet(const void * pTestee) const;
        private:
            virtual Leaf * CreateObject() const;

            std::string m_class;
            std::vector<std::string> m_words;

            bool InitializeWords();
            bool AddUserWord(const word::UserWord& uw);
            bool HaveChineseChar(const char * str);
        };

		class TypeCondition : public Leaf, public Condition
		{
		public:
			virtual bool CheckValid() const;
			virtual std::string GetName() const;
			virtual std::string GetDescription() const;
			virtual bool Configure(const std::string& str);
			virtual std::string GetConfiguration() const;
			virtual bool Meet(const void * pTestee) const;
		private:
			virtual Leaf * CreateObject() const;

			unsigned short m_type;
			std::string m_str_type;
		};

		class MiscCondition : public Leaf, public Condition
		{
		public:
			virtual bool CheckValid() const;
			virtual std::string GetName() const;
			virtual std::string GetDescription() const;
			virtual bool Configure(const std::string& str);
			virtual std::string GetConfiguration() const;
			virtual bool Meet(const void * pTestee) const;
		private:
			virtual Leaf * CreateObject() const;

			std::string m_cond_desc;
		};
    }
}