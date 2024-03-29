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

void Degree::removeChild(const QString &title)
{
    for(int i = 0; i < children_.size(); i++)
    {
        if(children_[i]->title() == title)
        {
            children_.removeAt(i);
            return;
        }
    }
}

void Degree::removeChildren()
{
    while(children_.size() > 0)
    {
        children_.first()->setParent(0);
        children_.pop_front();
    }
}

int Degree::quota(QString category) const
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

void Degree::setQuota(QString category, int quota)
{
    if(category.size() == 0)
        return;

    quotas_[category] = quota;
}
