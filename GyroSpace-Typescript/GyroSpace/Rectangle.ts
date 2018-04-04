class Rectangle {

    private m_left: number;
    private m_top: number;
    private m_right: number;
    private m_bottom: number;
    private m_width: number;
    private m_height: number;

    constructor(left: number, top: number, right: number, bottom: number) {
        this.m_left = left;
        this.m_top = top;
        this.m_right = right;
        this.m_bottom = bottom;
        this.m_width = right + left;
        this.m_height = bottom + top;
    }

    public get Left(): number {
        return this.m_left;
    }

    public get Top(): number {
        return this.m_top;
    }

    public get Right(): number {
        return this.m_right;
    }

    public get Bottom(): number {
        return this.m_bottom;
    }

    public get Width() {
        return this.m_width;
    }

    public get Height() {
        return this.m_height;
    }

    ////contains(rect: gsCRectangle) {
    ////    return (rect.Left >= this.m_rect.Left &&
    ////        rect.Right <= this.m_rect.Right &&
    ////        rect.Top >= this.m_rect.Top &&
    ////        rect.Bottom <= this.m_rect.Bottom);
    ////}

    ////Intersects(rect: Rectangle) {
    ////    return (this.Left < rect.Right &&
    ////        this.Right > rect.Left &&
    ////        this.Top < rect.Bottom &&
    ////        this.Bottom > rect.Top);
    ////}


    Intersects(rect: Rectangle) {


        //var one = Math.max(this.Left, rect.Left);
        //var two = Math.max(this.Top, rect.Top);
        //var three = Math.min(this.Right, rect.Right);
        //var four = Math.min(this.Bottom, rect.Bottom);


        //var result = (this.Left < rect.Right &&
        //    this.Right > rect.Left &&
        //    this.Top + this.Bottom < rect.Bottom &&
        //    this.Bottom > rect.Top);

        // Jet man
        var wtf: Rectangle = this.FromLTRB(this.Left, this.Top, this.Right, this.Bottom);
        // Ledge
        var wtf1: Rectangle = this.FromLTRB(rect.Left, rect.Top, rect.Right, rect.Bottom);


        var result1 = (wtf.Left < wtf1.Right &&
            wtf.Right > wtf1.Left &&
            wtf.Top < wtf1.Bottom &&
            wtf.Bottom > wtf1.Top);




       //// return result;

        return result1;


        ////return (wtf.Left < rect.Right &&
        ////    wtf.Right > rect.Left &&
        ////    wtf.Top < rect.Bottom &&
        ////    wtf.Bottom > rect.Top);
    }

    private FromLTRB(left: number, top: number, right: number, bottom: number) {
        //return new Rectangle(left, top, right, bottom);
        return new Rectangle(left, top, right + left, bottom + top);
    }
}

export = Rectangle;