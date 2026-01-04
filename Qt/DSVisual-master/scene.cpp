#include "scene.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsView>
#include <QMessageBox>
#include <QIntValidator>

static QColor BinTreeLeftLineColor(100, 100, 255);
static QColor BinTreeRightLineColor(255, 100, 100);

Scene::Scene(type t, QGraphicsView *view) : QGraphicsScene(view)
{
    m_type = t;
    m_mode = Normal;
    thrdState = -1;
    isAnimationState = false;
    p_graphicsView = view;
    p_graphicsView->setMouseTracking(true);
    tempLine = nullptr;
    setItemIndexMethod(QGraphicsScene::NoIndex);

    connect(this, &Scene::AnimationFinished, [=](){
        isAnimationState = false;
    });

    if(m_type == BinTreeScene)
    {//二叉树场景初始化
        InitBinTreeScene();
    }
}

Scene::~Scene()
{//删除所有结点
    for(auto it = nodeList.begin(); it != nodeList.end(); )
    {
        delete *it;
        nodeList.erase(it++);
    }
}

void Scene::showBinTreeTraversalAnimation(BinTreeOrder order)
{
    if(*nodeList.begin() == nullptr) return;
    isAnimationState = true;
    for(auto it : animQueue)
    {//停止所有动画
        it->stop();
    }
    animQueue.clear();
    std::list<BinTreeNode<QString> *> orderNodeList;
    BinTree::Traversal(order, (*nodeList.begin())->getBinTreeNode(), orderNodeList);
    for(auto it : orderNodeList)
    {
        if(it == nullptr) continue;
        NodeItem *item = it->p_item;
        QTimeLine *anim = item->getBounceAnimation();
        animQueue.push_back(anim);
    }
    //播放第一个动画
    animQueue.front()->start();
}

void Scene::showBinSortTreeFindNodeAnimation(int num)
{
    if(*nodeList.begin() == nullptr)
    {
        QMessageBox::information(p_graphicsView, "提示", "请先插入数据");
        return;
    }
    isAnimationState = true;
    for(auto it : animQueue)
    {//停止所有动画
        it->stop();
    }
    animQueue.clear();
    static std::list<BinTreeNode<int> *> orderNodeList;
    for(auto it : orderNodeList)
    {
        if(it == nullptr) continue;
        NodeItem *item = it->p_item;
        QTimeLine *anim = item->getBounceAnimation();
        animQueue.push_back(anim);
    }
    disconnect(this, &Scene::AnimationFinished, 0, 0);
    connect(this, &Scene::AnimationFinished, [&, num](){
        isAnimationState = false;
        if(orderNodeList.empty()) return;
        if((*orderNodeList.rbegin())->data != num)
        {
            QMessageBox::about(p_graphicsView, "查找结果", QString("未找到该数据,共遍历%1个结点").arg(orderNodeList.size()));
        }
        else
        {
            QMessageBox::about(p_graphicsView, "查找结果", QString("已找到该数据,共遍历%1个结点").arg(orderNodeList.size()));
        }
        orderNodeList.clear();
    });

    //播放第一个动画
    animQueue.front()->start();
}

void Scene::showBinTreeThreaded(BinTreeOrder order)
{//线索化
    thrdState = order;
    hideBinTreeThreaded();
    std::list<BinTreeNode<QString> *> orderNodeList;
    BinTree::Traversal(order, (*nodeList.begin())->getBinTreeNode(), orderNodeList);

    auto orderNodeList_frist = orderNodeList.begin();
    auto orderNodeList_last = orderNodeList.end();
    orderNodeList_last--;
    for(auto iter = orderNodeList.begin(); iter != orderNodeList.end(); iter++)
    {
        if((*iter)->left == nullptr && iter != orderNodeList_frist)
        {//左结点为空 且不为序列链表的头结点
            auto pre = iter;
            pre--;
            NodeItem *beginItem = (*iter)->p_item;
            NodeItem *endItem = (*pre)->p_item;
            LineItem *arc = new LineItem(LineItem::SingleArrow, beginItem, endItem);
            arc->setArc(true);
            QPen pen(BinTreeLeftLineColor);
            pen.setStyle(Qt::DashLine);
            pen.setWidth(3);
            arc->setPen(pen);
            auto iter_thrdLine_pre = beginItem->getLines().begin();
            auto iter_child_parentThrdLine_pre = endItem->getParentLines().begin();
            for(int i = 0; i < 2; i++)
            {
                iter_thrdLine_pre++;
                iter_child_parentThrdLine_pre++;
            }
            *iter_thrdLine_pre = arc;
            *iter_child_parentThrdLine_pre = arc;
            addItem(arc);
        }
        if((*iter)->right == nullptr && iter != orderNodeList_last)
        {//右结点为空 且不为序列链表的尾结点
            auto next = iter;
            next++;
            NodeItem *beginItem = (*iter)->p_item;
            NodeItem *endItem = (*next)->p_item;
            LineItem *arc = new LineItem(LineItem::SingleArrow, beginItem, endItem);
            arc->setArc(true);
            QPen pen(BinTreeRightLineColor);
            pen.setStyle(Qt::DashLine);
            pen.setWidth(3);
            arc->setPen(pen);
            auto iter_thrdLine_next = beginItem->getLines().begin();
            auto iter_child_parentThrdLine_next = endItem->getParentLines().begin();
            for(int i = 0; i < 3; i++)
            {
                iter_thrdLine_next++;
                iter_child_parentThrdLine_next++;
            }
            *iter_thrdLine_next = arc;
            *iter_child_parentThrdLine_next = arc;
            addItem(arc);
        }
    }
}

void Scene::showBinTreeLevelorderThreaded()
{// 层序遍历线索化
    thrdState = Levelorder;
    hideBinTreeThreaded();
    std::list<BinTreeNode<QString> *> orderNodeList;
    std::queue<BinTreeNode<QString> *> nodeQueue;
    if (*nodeList.begin() != nullptr) {
        nodeQueue.push((*nodeList.begin())->getBinTreeNode());
    }
    while (!nodeQueue.empty()) {
        BinTreeNode<QString> *node = nodeQueue.front();
        nodeQueue.pop();
        orderNodeList.push_back(node);
        if (node->left != nullptr) {
            nodeQueue.push(node->left);
        }
        if (node->right != nullptr) {
            nodeQueue.push(node->right);
        }
    }

    auto orderNodeList_frist = orderNodeList.begin();
    auto orderNodeList_last = orderNodeList.end();
    orderNodeList_last--;
    for (auto iter = orderNodeList.begin(); iter != orderNodeList.end(); iter++) {
        if ((*iter)->left == nullptr && iter != orderNodeList_frist)
        {// 左结点为空 且不为序列链表的头结点
            auto pre = iter;
            pre--;
            NodeItem *beginItem = (*iter)->p_item;
            NodeItem *endItem = (*pre)->p_item;
            LineItem *arc = new LineItem(LineItem::SingleArrow, beginItem, endItem);
            arc->setArc(true);
            QPen pen(BinTreeLeftLineColor);
            pen.setStyle(Qt::DashLine);
            pen.setWidth(3);
            arc->setPen(pen);
            auto iter_thrdLine_pre = beginItem->getLines().begin();
            auto iter_child_parentThrdLine_pre = endItem->getParentLines().begin();
            for (int i = 0; i < 2; i++) {
                iter_thrdLine_pre++;
                iter_child_parentThrdLine_pre++;
            }
            *iter_thrdLine_pre = arc;
            *iter_child_parentThrdLine_pre = arc;
            addItem(arc);
        }
        if ((*iter)->right == nullptr && iter != orderNodeList_last)
        {// 右结点为空 且不为序列链表的尾结点
            auto next = iter;
            next++;
            NodeItem *beginItem = (*iter)->p_item;
            NodeItem *endItem = (*next)->p_item;
            LineItem *arc = new LineItem(LineItem::SingleArrow, beginItem, endItem);
            arc->setArc(true);
            QPen pen(BinTreeRightLineColor);
            pen.setStyle(Qt::DashLine);
            pen.setWidth(3);
            arc->setPen(pen);
            auto iter_thrdLine_next = beginItem->getLines().begin();
            auto iter_child_parentThrdLine_next = endItem->getParentLines().begin();
            for (int i = 0; i < 3; i++) {
                iter_thrdLine_next++;
                iter_child_parentThrdLine_next++;
            }
            *iter_thrdLine_next = arc;
            *iter_child_parentThrdLine_next = arc;
            addItem(arc);
        }
    }
}

void Scene::hideBinTreeThreaded()
{//删除线索化连线
    for(auto it : nodeList)
    {
        auto iter_thrdLine_pre = it->getLines().begin();
        auto iter_thrdLine_next = it->getLines().begin();
        auto iter_parentThrdLine_pre = it->getParentLines().begin();
        auto iter_parentThrdLine_next = it->getParentLines().begin();
        for(int i = 0; i < 2; i++)
        {
            iter_thrdLine_pre++;
            iter_parentThrdLine_pre++;
        }
        for(int i = 0; i < 3; i++)
        {
            iter_thrdLine_next++;
            iter_parentThrdLine_next++;
        }
        if(*iter_thrdLine_pre != nullptr)
        {
            removeItem(*iter_thrdLine_pre);
            delete *iter_thrdLine_pre;
        }
        if(*iter_thrdLine_next != nullptr)
        {
            removeItem(*iter_thrdLine_next);
            delete *iter_thrdLine_next;
        }
        *iter_thrdLine_pre = nullptr;
        *iter_thrdLine_next = nullptr;
        *iter_parentThrdLine_pre = nullptr;
        *iter_parentThrdLine_next = nullptr;
    }
}

void Scene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(event->delta() > 0) p_graphicsView->scale(1.2, 1.2);
    else p_graphicsView->scale(1.0 / 1.2, 1.0 / 1.2);
    QGraphicsScene::wheelEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mouseScenePos = event->scenePos();
    if(m_mode == Normal)
    {//普通模式下
        if(event->button() == Qt::RightButton && isAnimationState == false)
        {
            QPoint menuPos = event->screenPos() + QPoint(8, 8);
            if(selectedItems().size() >= 2)
            {//选中两个及以上元素 弹出menu_selectItem菜单
                menu_selectItem.exec(menuPos);
            }
            else if(focusItem() != nullptr)
            {//焦点元素存在 弹出menu_focusItem菜单
                menu_focusItem.exec(menuPos);
            }
            else
            {//无选择状态 弹出menu_pressSpace菜单
                menu_pressSpace.exec(menuPos);
            }
        }
    }
    else if(m_mode == Linked)
    {//连线模式下
        m_mode = Normal;
        QList<QGraphicsItem *> endItems = items(tempLine->line().p2());
        if(endItems.count() == 0)
        {//无效连线
            removeItem(tempLine);
            delete tempLine;
        }
        else
        {
            if(m_type == BinTreeScene)
            {//二叉树连线
                QGraphicsItem *endItem = endItems.first();
                NodeItem *beginNodeItem = tempLine->getBeginItem();
                //点中结点且不为起始结点 或点中结点上的文本框且不为起始结点上的文本框
                if((endItem->type() == NodeItem::Type && endItem != beginNodeItem) ||
                   (endItem->type() == TextItem::Type && endItem != beginNodeItem->getTextItem()))
                {
                    NodeItem *endNodeItem;
                    if(endItem->type() == TextItem::Type)
                    {//点中了文本框 转换为父结点
                        endNodeItem = dynamic_cast<NodeItem *>(dynamic_cast<TextItem *>(endItem)->parentItem());
                    }
                    else
                    {//点中了结点
                        endNodeItem = dynamic_cast<NodeItem *>(endItem);
                    }
                    if(endNodeItem->getBinTreeNode() != (*nodeList.begin())->getBinTreeNode())
                    {//连接非根结点
                        BinTreeLinkNode(tempLine->getBeginItem(), endNodeItem, binTreeLinkDir);
                    }
                    else
                    {
                        removeItem(tempLine);
                        delete tempLine;
                        QMessageBox::warning(p_graphicsView, "错误", "请勿连接根结点");
                    }
                }
                else
                {//无效连线
                    removeItem(tempLine);
                    delete tempLine;
                }

                //连线结束重新进行线索化
                if(thrdState != -1)
                {
                    showBinTreeThreaded(BinTreeOrder(thrdState));
                }
            }
            /*else if(m_type == TYPE)
            {

            }*/
        }
        tempLine = nullptr;
    }

    QGraphicsScene::mousePressEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {//空格键进入场景拖拽模式
        p_graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {//空格键退出场景拖拽模式
        p_graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_mode == Linked)
    {//连线模式下 连线开始
        QPointF p1 = tempLine->mapFromItem(tempLine->getBeginItem(), 50, 50);
        QPointF p2 = event->scenePos();
        QVector2D vec(p2 - p1);
        vec.normalize();
        vec *= 50;
        p1 += vec.toPointF();
        QLineF line(p1, p2);
        tempLine->setLine(line);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::BinTreeLinkNode(NodeItem *beginNodeItem, NodeItem *endNodeItem, BinTreeLinkDir dir)
{
        auto iter_childItem_parentLine_left = endNodeItem->getParentLines().begin();
        auto iter_childItem_parentLine_right = endNodeItem->getParentLines().begin();
        iter_childItem_parentLine_right++;
        LineItem *&childItem_parentLine_left = *iter_childItem_parentLine_left;
        LineItem *&childItem_parentLine_right = *iter_childItem_parentLine_right;
        if(*iter_childItem_parentLine_left != nullptr)
        {//该子树已有父结点 且为左子树 断开与父结点的连接
            NodeItem *parentItem = childItem_parentLine_left->getBeginItem();
            BinTreeNode<QString> *parentNode = parentItem->getBinTreeNode();
            parentNode->left = nullptr;
            *parentItem->getLines().begin() = nullptr;
            delete childItem_parentLine_left;
            childItem_parentLine_left = nullptr;
        }
        if(*iter_childItem_parentLine_right != nullptr)
        {//该子树已有父结点 且为右子树 断开与父结点的连接
            NodeItem *parentItem = childItem_parentLine_right->getBeginItem();
            BinTreeNode<QString> *parentNode = parentItem->getBinTreeNode();
            parentNode->right = nullptr;
            auto iter_child_parentLine_right = parentItem->getLines().begin();
            iter_child_parentLine_right++;
            *iter_child_parentLine_right = nullptr;
            delete childItem_parentLine_right;
            childItem_parentLine_right = nullptr;
        }

        if(dir == LinkLeft)
        {//连接左结点
            beginNodeItem->getBinTreeNode()->left = endNodeItem->getBinTreeNode();
            //第一根线代表左结点
            *beginNodeItem->getLines().begin() = tempLine;
            *endNodeItem->getParentLines().begin() = tempLine;
            tempLine->setBeginItem(beginNodeItem);
            tempLine->setEndItem(endNodeItem);
            tempLine->updateLine();
        }
        else if(dir == LinkRight)
        {//连接右结点
            beginNodeItem->getBinTreeNode()->right = endNodeItem->getBinTreeNode();
            //第二根线代表右结点
            auto begin_right = beginNodeItem->getLines().begin();
            auto end_right = endNodeItem->getLines().begin();
            auto parent_right = endNodeItem->getParentLines().begin();
            begin_right++;
            end_right++;
            parent_right++;
            *begin_right = tempLine;
            *parent_right = tempLine;
            tempLine->setBeginItem(beginNodeItem);
            tempLine->setEndItem(endNodeItem);
            tempLine->updateLine();
        }

        BinTreeNode<QString> *rootNode = (*nodeList.begin())->getBinTreeNode();
        //连接结束计算二叉树长度和深度
        emit BinTreeNodeCountChanged(BinTree::NodeCount(rootNode), BinTree::TreeDepth(rootNode));
}

void Scene::InitBinTreeScene()
{//二叉树场景初始化
    //创建根结点
    NodeItem *rootItem = new NodeItem(NodeItem::BinTreeNodeItem);
    rootItem->setBrush(Qt::yellow);
    rootItem->setBinTreeNodeData("root");
    rootItem->setZValue(1);
    nodeList.push_back(rootItem);
    addItem(rootItem);

    //菜单设置
    QAction *addNode = menu_pressSpace.addAction("添加结点");
    QAction *rmAllChild = menu_pressSpace.addAction("删除所有子结点");
    QAction *rmChildren = menu_selectItem.addAction("删除选中的结点");
    QAction *rmFocusChild = menu_focusItem.addAction("删除该结点");
    QAction *changeNodeText = menu_focusItem.addAction("修改数据");
    QAction *linkLeftChild = menu_focusItem.addAction("连接左子树");
    QAction *linkRightChild = menu_focusItem.addAction("连接右子树");

    connect(addNode, &QAction::triggered, [=](){
        //添加结点
        NodeItem *node = new NodeItem(NodeItem::BinTreeNodeItem);
        node->setBrush(Qt::green);
        static int id = 1;
        node->setBinTreeNodeData(QString::number(id++));
        node->setPos(mouseScenePos.x(), mouseScenePos.y());
        nodeList.push_back(node);
        addItem(node);
    });
    connect(rmAllChild, &QAction::triggered, [=](){
        //删除所有子结点
        auto iter = nodeList.begin();
        hideBinTreeThreaded();
        for(iter++; iter != nodeList.end(); )
        {
            delete *iter;
            nodeList.erase(iter++);
        }
        emit BinTreeNodeCountChanged(1, 1);
    });
    connect(rmChildren, &QAction::triggered, [=](){
        //删除选中的结点
        QList<QGraphicsItem *> items = selectedItems();
        //先断开线索连接 再删除结点
        hideBinTreeThreaded();
        for(auto iter = items.begin(); iter != items.end(); )
        {
            if(*iter == *nodeList.begin())
            {
                QMessageBox::warning(p_graphicsView, "错误", "请勿删除根结点");
                iter++;
            }
            else
            {
                delete *iter;
                nodeList.erase(std::find(nodeList.begin(), nodeList.end(), *iter++));
            }
        }
        BinTreeNode<QString> *rootNode = (*nodeList.begin())->getBinTreeNode();
        //删除结束计算二叉树长度和深度
        emit BinTreeNodeCountChanged(BinTree::NodeCount(rootNode), BinTree::TreeDepth(rootNode));
        //删除结束重新进行线索化
        if(thrdState != -1)
        {
            showBinTreeThreaded(BinTreeOrder(thrdState));
        }
    });
    connect(rmFocusChild, &QAction::triggered, [=](){
        //删除焦点结点
        QGraphicsItem *item = focusItem();
        auto item_iterator = std::find(nodeList.begin(), nodeList.end(), item);
        if(item_iterator == nodeList.begin())
        {
            QMessageBox::warning(p_graphicsView, "错误", "请勿删除根结点");
        }
        else
        {
            //先断开线索连接 再删除结点
            hideBinTreeThreaded();
            delete item;
            nodeList.erase(item_iterator);
            BinTreeNode<QString> *rootNode = (*nodeList.begin())->getBinTreeNode();
            //删除结束计算二叉树长度和深度
            emit BinTreeNodeCountChanged(BinTree::NodeCount(rootNode), BinTree::TreeDepth(rootNode));
            //删除结束重新进行线索化
            if(thrdState != -1)
            {
                showBinTreeThreaded(BinTreeOrder(thrdState));
            }
        }
    });
    connect(changeNodeText, &QAction::triggered, [=](){
        //修改结点数据
        static TextInputDialog inputDialog;
        static bool isDialogInit = false;
        if(!isDialogInit)
        {
            isDialogInit = true;
            inputDialog.setWindowTitle("修改数据");
            connect(&inputDialog, &TextInputDialog::inputted, [=](QString text){
                NodeItem *item = dynamic_cast<NodeItem *>(this->focusItem());
                item->setBinTreeNodeData(text);
            });
        }
        NodeItem *item = dynamic_cast<NodeItem *>(focusItem());
        inputDialog.setText(item->binTreeNodeData());
        inputDialog.exec();
    });
    connect(linkLeftChild, &QAction::triggered, [=](){
        //连接左子树
        NodeItem *beginItem = dynamic_cast<NodeItem *>(focusItem());
        if(beginItem->getBinTreeNode()->left != nullptr)
        {//已有左子树 断开左子树连接
            beginItem->getBinTreeNode()->left = nullptr;
            (*(*beginItem->getLines().begin())->getEndItem()->getParentLines().begin()) = nullptr;
            delete (*beginItem->getLines().begin());
            (*beginItem->getLines().begin()) = nullptr;
        }
        tempLine = new LineItem(LineItem::NoArrow, beginItem, nullptr);
        QPen pen(BinTreeLeftLineColor);
        pen.setWidth(3);
        tempLine->setPen(pen);
        addItem(tempLine);
        tempLine->setLine(QLineF(beginItem->mapFromItem(beginItem, 50, 50), beginItem->mapFromItem(beginItem, 50, 50)));
        binTreeLinkDir = LinkLeft;
        m_mode = Linked;
    });
    connect(linkRightChild, &QAction::triggered, [=](){
        //连接右子树
        NodeItem *beginItem = dynamic_cast<NodeItem *>(focusItem());
        if(beginItem->getBinTreeNode()->right != nullptr)
        {//已有右子树 断开右子树连接
            beginItem->getBinTreeNode()->right = nullptr;
            auto right = beginItem->getLines().begin();
            right++;
            auto it_parentLine = (*right)->getEndItem()->getParentLines().begin();
            it_parentLine++;
            (*it_parentLine) = nullptr;
            delete *right;
            *right = nullptr;
        }
        tempLine = new LineItem(LineItem::NoArrow, beginItem, nullptr);
        QPen pen(BinTreeRightLineColor);
        pen.setWidth(3);
        tempLine->setPen(pen);
        addItem(tempLine);
        tempLine->setLine(QLineF(beginItem->mapFromItem(beginItem, 50, 50), beginItem->mapFromItem(beginItem, 50, 50)));
        binTreeLinkDir = LinkRight;
        m_mode = Linked;
    });
}
