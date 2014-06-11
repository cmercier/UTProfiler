#include "degree.h"

Degree::Degree(Degree *parent):
    parent_(parent)
{
}

void Degree::addChild(Degree *child)
{
    if(!children_.contains(child))
        children_.push_back(child);
}

void Degree::addUv(const Uv *uv)
{
    if(!uvs_.contains(uv))
        uvs_.push_back(uv);
}

int Degree::depth() const
{
    if(parent_)
        return parent_->depth() + 1;

    return 0;
}

int Degree::quota(Category category) const
{
    if(quotas_.contains(category))
        return quotas_[category];
    return 0;
}

void Degree::setParent(Degree *parent)
{
    parent_ = parent;

    if(parent)
        parent->addChild(this);
}

void Degree::setQuota(Category category, int quota)
{
    if(quota <= 0)
    {
        if(quotas_.contains(category))
            quotas_.remove(category);
    }
    else
        quotas_[category] = quota;
}
