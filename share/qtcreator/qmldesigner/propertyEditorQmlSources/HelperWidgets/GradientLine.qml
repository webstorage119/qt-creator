/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

import QtQuick 2.1
import HelperWidgets 2.0

Item {
    width: 300
    height: 60

    property color currentColor
    property alias model: repeater.model

    property bool hasGradient: gradientModel.hasGradient

    onCurrentColorChanged: {
        gradientModel.setColor(colorLine.selectedIndex, currentColor)
        colorLine.invalidate()
    }

    function addGradient() {
        gradientModel.addGradient()
        colorLine.invalidate()
    }

    function deleteGradient() {
        gradientModel.deleteGradient()
    }

    function dec2hex(integer) {
        var string = Math.round(integer).toString(16)
        if (integer < 16) {
            string = "0" + string
        }
        return string;
    }

    function colorToString(color) {
        var string = "#"
        if (color.a < 1)
            string += dec2hex(color.a * 255)
        string += dec2hex(color.r * 255)
        string += dec2hex(color.g * 255)
        string += dec2hex(color.b * 255)

        return string;
    }

    Item {
        id: colorLine
        height: 80
        width: parent.width

        property int effectiveWidth: width - 10
        property int selectedIndex: 0

        function select(index) {
            for (var i = 0; i < repeater.model.count; i++) {
                repeater.itemAt(i).item.highlighted = false
            }

            if (repeater.model.count < index + 1)
                return;

            repeater.itemAt(index).item.highlighted = true
            colorLine.selectedIndex = index

            gradientModel.lock()
            currentColor = repeater.itemAt(index).item.color
            gradientModel.unlock()
        }

        function invalidate() {
            var gradientString = "import QtQuick 2.0; Gradient {"

            for (var i = 0; i < gradientModel.count; i++) {
                gradientString += "GradientStop {}"
            }
            gradientString += "}"

            var gradientObject = Qt.createQmlObject(gradientString, gradientRectangle, "test");

            for (i = 0; i < gradientModel.count; i++) {
                repeater.itemAt(i).item.y = 20 //fixes corner case for dragging overlapped items
                gradientObject.stops[i].color =  gradientModel.getColor(i)
                gradientObject.stops[i].position = gradientModel.getPosition(i)
            }

            gradientRectangle.gradient = gradientObject;
        }

        Column {
            anchors.fill: parent
            MouseArea {
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right

                onClicked: {
                    var currentPosition = mouseX / colorLine.effectiveWidth

                    gradientModel.addStop(currentPosition, currentColor)
                    colorLine.select(gradientModel.count - 1)
                    colorLine.invalidate()
                }
                Item {
                    id: stack
                    anchors.fill: parent
                }

                Repeater {
                    id: repeater
                    model: GradientModel {
                        anchorBackendProperty: anchorBackend
                        gradientPropertyName: "gradient"
                        id: gradientModel

                    }

                    delegate: Loader {
                        id: loader

                        sourceComponent: component
                        Binding {
                            target: loader.item
                            property: "color"
                            value: color
                        }
                        Binding {
                            target: loader.item
                            property: "x"
                            value: position === undefined ? 0 : colorLine.effectiveWidth * position
                        }
                        Binding {
                            target: loader.item
                            property: "index"
                            value: index
                        }
                        Binding {
                            target: loader.item
                            property: "readOnly"
                            value: readOnly !== undefined ? readOnly : false
                        }
                    }
                }
            }

            Component.onCompleted: {
                colorLine.select(0);
                colorLine.invalidate();
            }

            Item {
                height: 16
                anchors.left: parent.left
                anchors.right: parent.right
                Rectangle {
                    smooth: true
                    x: 0
                    y: 16
                    radius: 1
                    border.color: "#555555"
                    border.width: 1
                    width: parent.height
                    height: parent.width
                    id: gradientRectangle
                    gradient: Gradient {
                        id: gradient
                    }
                    transformOrigin: Item.TopLeft
                    rotation: 270
                }
            }
        }
    }

    Component {
        id: component
        Item {
            y: 20
            width: 10
            height: 20

            property alias color: rectangle.color
            property alias highlighted: canvas.highlighted

            Rectangle {
                id: rectangle
                width: 10
                height: 10
                color: "red"
                border.color: "gray"
                border.width: 1
                radius: 1

            }

            Canvas {
                id: canvas
                width: 10
                height: 10
                y: 10

                antialiasing: true

                property bool highlighted: false

                property color strokeStyle:  Qt.darker(fillStyle, 1.6)
                property color fillStyle: highlighted ? "lightGray" : "gray"

                onHighlightedChanged: requestPaint()

                onPaint: {
                    var ctx = canvas.getContext('2d')
                    ctx.save()

                    ctx.strokeStyle = canvas.strokeStyle
                    ctx.lineWidth = 1
                    ctx.fillStyle = canvas.fillStyle

                    var size = 10
                    var yOffset = 2

                    ctx.beginPath()
                    ctx.moveTo(0, yOffset)
                    ctx.lineTo(size, yOffset)
                    ctx.lineTo(size / 2, 5 + yOffset)
                    ctx.closePath()
                    ctx.fill()
                    ctx.stroke()

                    ctx.restore()
                }

            }

            property bool readOnly: false
            property int index: 0

            opacity: y < 20 ? y / 10 : 1

            Behavior on y {
                PropertyAnimation {
                    duration: 100
                }
            }

            Behavior on opacity {
                PropertyAnimation {
                    duration: 100
                }
            }

            MouseArea {
                anchors.fill: parent
                drag.target: parent
                drag.minimumX: 0
                drag.maximumX: colorLine.effectiveWidth
                drag.minimumY: !readOnly ? 0 : 20
                drag.maximumY: 20
                onPressed: {
                    colorLine.select(index);
                }

                onReleased: {
                    if (drag.active) {
                        gradientModel.setPosition(colorLine.selectedIndex, parent.x / colorLine.effectiveWidth)

                        if (parent.y < 10) {
                            if (!readOnly) {
                                colorLine.select(index - 1)
                                gradientModel.removeStop(index)
                            }
                        }
                        parent.y = 20
                        colorLine.invalidate()
                    }
                }
            }
        }
    }
}
