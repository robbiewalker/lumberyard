/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once

#include <GraphCanvas/Widgets/NodePalette/TreeItems/DraggableNodePaletteTreeItem.h>
#include "CreateNodeMimeEvent.h"

#include <ScriptCanvas/GraphCanvas/NodeDescriptorBus.h>

namespace ScriptCanvasEditor
{
    // <EbusSender>
    class CreateEBusSenderMimeEvent
        : public CreateNodeMimeEvent
    {
    public:
        AZ_RTTI(CreateEBusSenderMimeEvent, "{7EFA0742-BBF6-45FD-B378-C73577DEE464}", CreateNodeMimeEvent);
        AZ_CLASS_ALLOCATOR(CreateEBusSenderMimeEvent, AZ::SystemAllocator, 0);
        static void Reflect(AZ::ReflectContext* reflectContext);

        CreateEBusSenderMimeEvent() = default;
        CreateEBusSenderMimeEvent(AZStd::string_view busName, AZStd::string_view eventName);
        ~CreateEBusSenderMimeEvent() = default;

    protected:
        ScriptCanvasEditor::NodeIdPair CreateNode(const AZ::EntityId& graphId) const override;
        
    private:

        AZStd::string m_busName;
        AZStd::string m_eventName;
    };
    
    class EBusSendEventPaletteTreeItem
        : public GraphCanvas::DraggableNodePaletteTreeItem
    {
    private:
        static const QString& GetDefaultIcon();
        
    public:
        AZ_CLASS_ALLOCATOR(EBusSendEventPaletteTreeItem, AZ::SystemAllocator, 0);
        AZ_RTTI(EBusSendEventPaletteTreeItem, "{26258B0A-8E2C-434D-ACAD-3DE85E64A4F8}", GraphCanvas::DraggableNodePaletteTreeItem);

        EBusSendEventPaletteTreeItem(AZStd::string_view busName, AZStd::string_view eventName, const ScriptCanvas::EBusBusId& busId, const ScriptCanvas::EBusEventId& eventIdentifier);
        ~EBusSendEventPaletteTreeItem() = default;
        
        GraphCanvas::GraphCanvasMimeEvent* CreateMimeEvent() const override;

        AZStd::string GetBusName() const;
        AZStd::string GetEventName() const;

        ScriptCanvas::EBusBusId GetBusId() const;
        ScriptCanvas::EBusEventId GetEventId() const;

    private:
    
        QString m_busName;
        QString m_eventName;

        ScriptCanvas::EBusBusId   m_busId;
        ScriptCanvas::EBusEventId m_eventId;
    };
    
    // </EbusSender>

    // <EbusHandler>
    class CreateEBusHandlerMimeEvent
        : public CreateNodeMimeEvent
    {
    public:
        AZ_RTTI(CreateEBusHandlerMimeEvent, "{7B205AA9-2A27-4508-9277-FB8D5C6BE5BC}", CreateNodeMimeEvent);
        AZ_CLASS_ALLOCATOR(CreateEBusHandlerMimeEvent, AZ::SystemAllocator, 0);
        static void Reflect(AZ::ReflectContext* reflectContext);

        CreateEBusHandlerMimeEvent() = default;
        CreateEBusHandlerMimeEvent(AZStd::string_view busName);
        ~CreateEBusHandlerMimeEvent() = default;

    protected:
        ScriptCanvasEditor::NodeIdPair CreateNode(const AZ::EntityId& graphId) const override;

    private:
        AZStd::string m_busName;
    };
    // </EbusHandler>

    // <EbusHandlerEvent>
    class CreateEBusHandlerEventMimeEvent
        : public SpecializedCreateNodeMimeEvent
    {
    public:
        AZ_RTTI(CreateEBusHandlerEventMimeEvent, "{0F5FAB1D-7E84-44E6-8161-630576490249}", SpecializedCreateNodeMimeEvent);
        AZ_CLASS_ALLOCATOR(CreateEBusHandlerEventMimeEvent, AZ::SystemAllocator, 0);
        
        static void Reflect(AZ::ReflectContext* reflectContext);
        
        CreateEBusHandlerEventMimeEvent() = default;
        CreateEBusHandlerEventMimeEvent(AZStd::string_view busName, AZStd::string_view methodName, const ScriptCanvas::EBusEventId& eventId);
        ~CreateEBusHandlerEventMimeEvent() = default;

        AZStd::string_view GetBusName() { return m_busName; }
        AZStd::string_view GetEventName() { return m_eventName; }
        ScriptCanvas::EBusEventId GetEventId() { return m_eventId; }

        NodeIdPair ConstructNode(const AZ::EntityId& graphCanvasGraphId, const AZ::Vector2& scenePosition) override;
        bool ExecuteEvent(const AZ::Vector2& mousePosition, AZ::Vector2& sceneDropPosition, const AZ::EntityId& graphCanvasGraphId) override;

        NodeIdPair CreateEventNode(const AZ::EntityId& graphCanvasGraphId, const AZ::Vector2& scenePosition) const;

    private:
        AZStd::string m_busName;
        AZStd::string m_eventName;

        ScriptCanvas::EBusEventId m_eventId;
    };
    
    // These nodes will create a purely visual representation of the data. They do not have a corresponding ScriptCanvas node, but instead
    // share slots from the owning EBus Handler node. This creates a bit of weirdness with the general creation, since we no longer have a 1:1
    // and need to create a bus wrapper for these things whenever we try to make them.
    class EBusHandleEventPaletteTreeItem
        : public GraphCanvas::DraggableNodePaletteTreeItem
    {
    private:
        static const QString& GetDefaultIcon();
        
    public:
        AZ_CLASS_ALLOCATOR(EBusHandleEventPaletteTreeItem, AZ::SystemAllocator, 0);
        AZ_RTTI(EBusHandleEventPaletteTreeItem, "{99A95EC0-1DF8-45B8-8229-D6D12E32CBED}", GraphCanvas::DraggableNodePaletteTreeItem);

        EBusHandleEventPaletteTreeItem(AZStd::string_view busName, AZStd::string_view eventName, const ScriptCanvas::EBusBusId& busId, const ScriptCanvas::EBusEventId& eventId);
        ~EBusHandleEventPaletteTreeItem() = default;
        
        GraphCanvas::GraphCanvasMimeEvent* CreateMimeEvent() const override;

        AZStd::string GetBusName() const;
        AZStd::string GetEventName() const;

        ScriptCanvas::EBusBusId GetBusId() const;
        ScriptCanvas::EBusEventId GetEventId() const;

    private:
        AZStd::string m_busName;
        AZStd::string m_eventName;

        ScriptCanvas::EBusBusId   m_busId;
        ScriptCanvas::EBusEventId m_eventId;
    };
    
    // </EbusHandlerEvent>
}