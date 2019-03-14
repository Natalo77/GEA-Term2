#include "AStar_Node.h"
#include "AStar_Edge.h"


AStar_Node::AStar_Node()
{
}


AStar_Node::~AStar_Node()
{
}

AStar_Node::AStar_Node(Vector2 * position)
{
	m_neighbours = new std::vector<AStar_Edge*>();
	m_position = position;
}

bool AStar_Node::isEqual(AStar_Node * rhs)
{
	return (m_position->distance(*rhs->getPosition()) < 0.01f);
}

float AStar_Node::getF()
{
	return m_g + m_h;
}

void AStar_Node::setG(float g)
{
	this->m_g = g;
}

void AStar_Node::setH(float h)
{
	this->m_h = h;
}

std::vector<AStar_Edge*>* AStar_Node::getNeighbours()
{
	return m_neighbours;
}

bool AStar_Node::isVisited()
{
	return m_visited;
}

void AStar_Node::setVisited(bool visited)
{
	this->m_visited = visited;
}

AStar_Node * AStar_Node::getParent()
{
	return m_parent;
}

Vector2 * AStar_Node::getPosition()
{
	return m_position;
}
