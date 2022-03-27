#pragma once

#include "core/Writer.h"

#include <memory>

class WritableUnit
{
public:
	template<typename T>
	WritableUnit(T parameter) : m_self(std::make_unique<Model<T>>(std::move(parameter))) { }
	~WritableUnit() { }

	WritableUnit(const WritableUnit &object) : m_self(object.m_self->copy()) { }
	WritableUnit(WritableUnit &&) noexcept = default;

	WritableUnit &operator=(const WritableUnit &object) { return *this = WritableUnit(object); }
	WritableUnit &operator=(WritableUnit &&) noexcept = default;

	friend void write(const WritableUnit &parameter, std::stringstream &out, std::size_t position) { parameter.m_self->write(out, position); }
private:
	struct Concept_T
	{
		Concept_T() = default;
		virtual ~Concept_T() = default;
		
		virtual std::unique_ptr<Concept_T> copy() const = 0;
		virtual void write(std::stringstream&, std::size_t) const = 0;
	};

	template<typename T>
	struct Model final : public Concept_T
	{
		Model(T data) : m_data(data) { }
		~Model() { }

		std::unique_ptr<Concept_T> copy() const override { return std::make_unique<Model>(*this); }
		void write(std::stringstream &out, std::size_t position) const override { ::write(m_data, out, position); }

		T m_data;
	};

	std::unique_ptr<Concept_T> m_self;
};

